"""Tests for ligand functionality."""
import logging
from math import isclose
from pathlib import Path
import pytest
import pandas as pd
from numpy.testing import assert_almost_equal
from pdb2pqr.ligand.mol2 import Mol2Molecule
import common
from ligand_results import TORSION_RESULTS, RING_RESULTS
from ligand_results import FORMAL_CHARGE_RESULTS, PARAMETER_RESULTS


_LOGGER = logging.getLogger(__name__)
_LOGGER.warning("Need functional and regression test coverage for --ligand")


ALL_LIGANDS = set(TORSION_RESULTS) | set(RING_RESULTS)
ALL_LIGANDS |= {
    "1HPX-ligand.mol2", "1QBS-ligand.mol2", "1US0-ligand.mol2", "adp.mol2",
    "acetate.mol2"}
ALL_LIGANDS = sorted(list(ALL_LIGANDS))


@pytest.mark.parametrize("input_mol2", ALL_LIGANDS)
def test_assign_parameters(input_mol2):
    """Testing basic aspects of code breaking."""
    ligand = Mol2Molecule()
    mol2_path = Path("tests/data") / input_mol2
    with open(mol2_path, "rt") as mol2_file:
        ligand.read(mol2_file)
    old_total_charge = 0
    for atom in ligand.atoms.values():
        old_total_charge += atom.formal_charge
    ligand.assign_parameters()
    new_total_charge = 0
    test_results = []
    for atom in ligand.atoms.values():
        test_row = {
            "name": atom.name, "type": atom.type, "charge": atom.charge,
            "radius": atom.radius}
        test_results.append(test_row)
        new_total_charge += atom.charge
    _LOGGER.debug("Test results: %s", test_results)
    test_results = pd.DataFrame(test_results)
    test_results = test_results.set_index("name")
    # _LOGGER.debug("Test results:\n%s", test_results.to_string())
    _LOGGER.info(
        "Total charge: %5.2f -> %5.2f", old_total_charge, new_total_charge)
    expected_results = pd.DataFrame(PARAMETER_RESULTS[input_mol2])
    expected_results = expected_results.set_index("name")
    assert_almost_equal(
        test_results["charge"].to_numpy(),
        expected_results["charge"].to_numpy())
    assert_almost_equal(
        test_results["radius"].to_numpy(),
        expected_results["radius"].to_numpy(), verbose=True)


@pytest.mark.parametrize("input_mol2", ALL_LIGANDS)
def test_formal_charge(input_mol2):
    """Testing formal charge calculation."""
    ligand = Mol2Molecule()
    mol2_path = Path("tests/data") / input_mol2
    with open(mol2_path, "rt") as mol2_file:
        ligand.read(mol2_file)
    expected_results = FORMAL_CHARGE_RESULTS[input_mol2]
    errors = []
    for iatom, atom in enumerate(ligand.atoms.values()):
        try:
            expected_charge = expected_results[iatom]
        except IndexError:
            err = (
                "Missing result for {a.name}, {a.type}, {a.formal_charge}")
            err = err.format(a=atom)
            raise IndexError(err)
        if not isclose(atom.formal_charge, expected_charge):
            err = (
                "Atom {0.name} {0.type} with bond order "
                "{0.bond_order}: expected {1}, got {2}")
            err = err.format(atom, expected_charge, atom.formal_charge)
            errors.append(err)
    if len(errors) > 0:
        err = "Errors in test values:\n%s" % "\n".join(errors)
        raise ValueError(err)


@pytest.mark.parametrize("input_mol2", TORSION_RESULTS)
def test_torsions(input_mol2):
    """Test assignment of torsion angles."""
    ligand = Mol2Molecule()
    mol2_path = Path("tests/data") / input_mol2
    with open(mol2_path, "rt") as mol2_file:
        ligand.read(mol2_file)
    test = set()
    # Only test heavy-atom torsions
    for torsion in ligand.torsions:
        has_hydrogen = False
        for atom in torsion:
            if atom.startswith("H"):
                has_hydrogen = True
        if not has_hydrogen:
            test.add(torsion)
    try:
        expected = TORSION_RESULTS[input_mol2]
        diff = test ^ expected
        if len(diff) > 0:
            err = (
                "Torsion test failed for {mol}:\n"
                "Got: {test}\n"
                "Expected: {expected}\n"
                "Difference: {diff}").format(
                    mol=input_mol2, test=sorted(list(test)),
                    expected=sorted(list(expected)), diff=sorted(list(diff)))
            raise ValueError(err)
    except KeyError:
        err = "No results for %s: %s", input_mol2, sorted(
            list(ligand.torsions))
        raise KeyError(err)


@pytest.mark.parametrize("input_mol2", ALL_LIGANDS)
def test_rings(input_mol2):
    """Test assignment of torsion angles."""
    ligand = Mol2Molecule()
    mol2_path = Path("tests/data") / input_mol2
    with open(mol2_path, "rt") as mol2_file:
        ligand.read(mol2_file)
    test = ligand.rings
    try:
        benchmark = RING_RESULTS[input_mol2]
    except KeyError:
        err = "Missing expected results for %s: %s" % (
            input_mol2, test)
        raise KeyError(err)
    diff = test ^ benchmark
    if len(diff) > 0:
        err = (
            "Ring test failed for {mol}:\n"
            "Got: {test}\n"
            "Expected: {expected}\n"
            "Difference: {diff}").format(
                mol=input_mol2, test=sorted(list(test)),
                expected=sorted(list(benchmark)),
                diff=sorted(list(diff)))
        raise ValueError(err)
    for atom_name in ligand.atoms:
        atom = ligand.atoms[atom_name]
        if atom.num_rings > 0:
            str_ = "%d rings: %s" % (atom.num_rings, atom)
            _LOGGER.debug(str_)


@pytest.mark.parametrize(
    "input_pdb", ["1HPX"], ids=str)
def test_ligand_protein(input_pdb, tmp_path):
    """PROPKA non-regression tests on proteins without ligands."""
    input_pdb = Path(input_pdb)
    ligand = Path("tests/data") / ("%s-ligand.mol2" % input_pdb.stem)
    args = "--log-level=INFO --ff=AMBER --drop-water --ligand=%s" % ligand
    output_pqr = Path(input_pdb).stem + ".pqr"
    _LOGGER.debug("Running test in %s", tmp_path)
    common.run_pdb2pqr(
        args=args, input_pdb=input_pdb, output_pqr=output_pqr,
        tmp_path=tmp_path)


# @pytest.mark.parametrize(
#     "args, input_pdb, input_mol2, output_pqr",
#     [
#         pytest.param(
#             "--log-level=INFO --ff=AMBER",
#             "1HPX",
#             common.DATA_DIR / "1HPX-ligand.mol2",
#             "output.pqr",
#             id="1HPX-ligand AMBER"
#         ),
#         pytest.param(
#             "--log-level=INFO --ff=AMBER",
#             common.DATA_DIR / "1QBS.pdb",
#             common.DATA_DIR / "1QBS-ligand.mol2",
#             "output.pqr",
#             id="1QBS-ligand AMBER"
#         ),
#         pytest.param(
#             "--log-level=INFO --ff=AMBER",
#             common.DATA_DIR / "1US0.pdb",
#             common.DATA_DIR / "1US0-ligand.mol2",
#             "output.pqr",
#             id="1US0-ligand AMBER"
#         ),
#     ]
# )
# def test_ligand(args, input_pdb, input_mol2, output_pqr, tmp_path):
#     """Test ligand handling."""
#     args_ = "{args} --ligand={ligand}".format(args=args, ligand=input_mol2)
#     run_pdb2pqr(args_, input_pdb, output_pqr, tmp_path)
#     _LOGGER.warning("This test needs better checking to avoid silent failure.")
