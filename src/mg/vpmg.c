/* ///////////////////////////////////////////////////////////////////////////
/// APBS -- Adaptive Poisson-Boltzmann Solver
///
///  Nathan A. Baker (nbaker@wasabi.ucsd.edu)
///  Dept. of Chemistry and Biochemistry
///  Dept. of Mathematics, Scientific Computing Group
///  University of California, San Diego 
///
///  Additional contributing authors listed in the code documentation.
///
/// Copyright � 1999. The Regents of the University of California (Regents).
/// All Rights Reserved. 
/// 
/// Permission to use, copy, modify, and distribute this software and its
/// documentation for educational, research, and not-for-profit purposes,
/// without fee and without a signed licensing agreement, is hereby granted,
/// provided that the above copyright notice, this paragraph and the
/// following two paragraphs appear in all copies, modifications, and
/// distributions.
/// 
/// IN NO EVENT SHALL REGENTS BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT,
/// SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS,
/// ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF
/// REGENTS HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  
/// 
/// REGENTS SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT
/// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
/// PARTICULAR PURPOSE.  THE SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF
/// ANY, PROVIDED HEREUNDER IS PROVIDED "AS IS".  REGENTS HAS NO OBLIGATION
/// TO PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR
/// MODIFICATIONS. 
//////////////////////////////////////////////////////////////////////////// 
/// rcsid="$Id$"
//////////////////////////////////////////////////////////////////////////// */

/* ///////////////////////////////////////////////////////////////////////////
// File:     vpmg.c
//
// Purpose:  Class Vpmg: methods.
//
// Author:   Nathan Baker
/////////////////////////////////////////////////////////////////////////// */

#include "apbscfg.h"
#include "vpmg-private.h"
#include "apbs/vpmg.h"

#define VPMGSMALL 1e-14

VEMBED(rcsid="$Id$")

/* ///////////////////////////////////////////////////////////////////////////
// Class Vpmg: Inlineable methods
/////////////////////////////////////////////////////////////////////////// */
#if !defined(VINLINE_VACC)
#endif /* if !defined(VINLINE_VACC) */

/* ///////////////////////////////////////////////////////////////////////////
// Class Vpmg: Non-inlineable methods
/////////////////////////////////////////////////////////////////////////// */

/* ///////////////////////////////////////////////////////////////////////////
// Routine:  focusFillBound
//
// Purpose:  Fill boundaries with old values before destroying
//
// Author:   Nathan Baker
/////////////////////////////////////////////////////////////////////////// */
VPRIVATE void focusFillBound(Vpmg *thee, Vpmg *pmgOLD) {

    double hxOLD, hyOLD, hzOLD, xminOLD, yminOLD, zminOLD, xmaxOLD, ymaxOLD;
    double zmaxOLD;
    int nxOLD, nyOLD, nzOLD;
    double hxNEW, hyNEW, hzNEW, xminNEW, yminNEW, zminNEW, xmaxNEW, ymaxNEW;
    double zmaxNEW;
    int nxNEW, nyNEW, nzNEW;
    int i, j, k, ihi, ilo, jhi, jlo, khi, klo, nx, ny, nz;
    double x, y, z, dx, dy, dz, ifloat, jfloat, kfloat, uval;


    /* Calculate new problem dimensions */
    hxNEW = thee->pmgp->hx;
    hyNEW = thee->pmgp->hy;
    hzNEW = thee->pmgp->hzed;
    nxNEW = thee->pmgp->nx;
    nyNEW = thee->pmgp->ny;
    nzNEW = thee->pmgp->nz;
    xminNEW = thee->pmgp->xcent - ((double)(nxNEW-1)*hxNEW)/2.0;
    xmaxNEW = thee->pmgp->xcent + ((double)(nxNEW-1)*hxNEW)/2.0;
    yminNEW = thee->pmgp->ycent - ((double)(nyNEW-1)*hyNEW)/2.0;
    ymaxNEW = thee->pmgp->ycent + ((double)(nyNEW-1)*hyNEW)/2.0;
    zminNEW = thee->pmgp->zcent - ((double)(nzNEW-1)*hzNEW)/2.0;
    zmaxNEW = thee->pmgp->zcent + ((double)(nzNEW-1)*hzNEW)/2.0;

    /* Relevant old problem parameters */
    hxOLD = pmgOLD->pmgp->hx;
    hyOLD = pmgOLD->pmgp->hy;
    hzOLD = pmgOLD->pmgp->hzed;
    nxOLD = pmgOLD->pmgp->nx;
    nyOLD = pmgOLD->pmgp->ny;
    nzOLD = pmgOLD->pmgp->nz;
    xminOLD = pmgOLD->pmgp->xcent - ((double)(nxOLD-1)*hxOLD)/2.0;
    xmaxOLD = pmgOLD->pmgp->xcent + ((double)(nxOLD-1)*hxOLD)/2.0;
    yminOLD = pmgOLD->pmgp->ycent - ((double)(nyOLD-1)*hyOLD)/2.0;
    ymaxOLD = pmgOLD->pmgp->ycent + ((double)(nyOLD-1)*hyOLD)/2.0;
    zminOLD = pmgOLD->pmgp->zcent - ((double)(nzOLD-1)*hzOLD)/2.0;
    zmaxOLD = pmgOLD->pmgp->zcent + ((double)(nzOLD-1)*hzOLD)/2.0;

    /* Sanity check: make sure we're within the old mesh */
    if (((xmaxNEW-xmaxOLD)>VPMGSMALL) || 
        ((ymaxNEW-ymaxOLD)>VPMGSMALL) || 
        ((zmaxNEW-zmaxOLD)>VPMGSMALL) ||
        ((xminOLD-xminNEW)>VPMGSMALL) || 
        ((yminOLD-yminNEW)>VPMGSMALL) || 
        ((zminOLD-zminNEW)>VPMGSMALL)) {
        Vnm_print(2, "VPMG::focusFillBound -- new mesh not contained in old!\n");
        Vnm_print(2, "VPMG::focusFillBound -- New mesh mins = %g, %g, %g\n",
          xminNEW, yminNEW, zminNEW);
        Vnm_print(2, "VPMG::focusFillBound -- New mesh maxs = %g, %g, %g\n",
          xmaxNEW, ymaxNEW, zmaxNEW);
        Vnm_print(2, "VPMG::focusFillBound -- Old mesh mins = %g, %g, %g\n",
          xminOLD, yminOLD, zminOLD);
        Vnm_print(2, "VPMG::focusFillBound -- Old mesh maxs = %g, %g, %g\n",
          xmaxOLD, ymaxOLD, zmaxOLD);
        fflush(stderr);
        VASSERT(0);
    }

    
    /* Fill the "i" boundaries (dirichlet) */
    for (k=0; k<nzNEW; k++) {
        for (j=0; j<nyNEW; j++) {
            /* Low X face */
            x = xminNEW;
            y = yminNEW + j*hyNEW;
            z = zminNEW + k*hzNEW;
            ifloat = (x - xminOLD)/hxOLD;
            jfloat = (y - yminOLD)/hyOLD;
            kfloat = (z - zminOLD)/hzOLD;
            ihi = (int)ceil(ifloat);
            if (ihi > (nxOLD-1)) ihi = nxOLD-1;
            ilo = (int)floor(ifloat);
            if (ilo < 0) ilo = 0;
            jhi = (int)ceil(jfloat);
            if (jhi > (nyOLD-1)) jhi = nyOLD-1;
            jlo = (int)floor(jfloat);
            if (jlo < 0) jlo = 0;
            khi = (int)ceil(kfloat);
            if (khi > (nzOLD-1)) khi = nzOLD-1;
            klo = (int)floor(kfloat);
            if (klo < 0) klo = 0;
            dx = ifloat - (double)(ilo);
            dy = jfloat - (double)(jlo);
            dz = kfloat - (double)(klo);
            nx = nxOLD; ny = nyOLD; nz = nzOLD;
            uval =  dx*dy*dz*(pmgOLD->u[IJK(ihi,jhi,khi)])
                  + dx*(1.0-dy)*dz*(pmgOLD->u[IJK(ihi,jlo,khi)])
                  + dx*dy*(1.0-dz)*(pmgOLD->u[IJK(ihi,jhi,klo)])
                  + dx*(1.0-dy)*(1.0-dz)*(pmgOLD->u[IJK(ihi,jlo,klo)])
                  + (1.0-dx)*dy*dz*(pmgOLD->u[IJK(ilo,jhi,khi)])
                  + (1.0-dx)*(1.0-dy)*dz*(pmgOLD->u[IJK(ilo,jlo,khi)])
                  + (1.0-dx)*dy*(1.0-dz)*(pmgOLD->u[IJK(ilo,jhi,klo)])
                  + (1.0-dx)*(1.0-dy)*(1.0-dz)*(pmgOLD->u[IJK(ilo,jlo,klo)]);
            nx = nxNEW; ny = nyNEW; nz = nzNEW;
            thee->gxcf[IJKx(j,k,0)] = uval;

            /* High X face */
            x = xmaxNEW;
            ifloat = (x - xminOLD)/hxOLD;
            ihi = (int)ceil(ifloat);
            if (ihi > (nxOLD-1)) ihi = nxOLD-1;
            ilo = (int)floor(ifloat);
            if (ilo < 0) ilo = 0;
            dx = ifloat - (double)(ilo);
            nx = nxOLD; ny = nyOLD; nz = nzOLD;
            uval =  dx*dy*dz*(pmgOLD->u[IJK(ihi,jhi,khi)])
                  + dx*(1.0-dy)*dz*(pmgOLD->u[IJK(ihi,jlo,khi)])
                  + dx*dy*(1.0-dz)*(pmgOLD->u[IJK(ihi,jhi,klo)])
                  + dx*(1.0-dy)*(1.0-dz)*(pmgOLD->u[IJK(ihi,jlo,klo)])
                  + (1.0-dx)*dy*dz*(pmgOLD->u[IJK(ilo,jhi,khi)])
                  + (1.0-dx)*(1.0-dy)*dz*(pmgOLD->u[IJK(ilo,jlo,khi)])
                  + (1.0-dx)*dy*(1.0-dz)*(pmgOLD->u[IJK(ilo,jhi,klo)])
                  + (1.0-dx)*(1.0-dy)*(1.0-dz)*(pmgOLD->u[IJK(ilo,jlo,klo)]);
            nx = nxNEW; ny = nyNEW; nz = nzNEW;
            thee->gxcf[IJKx(j,k,1)] = uval;
            
            /* Zero Neumann conditions */             
            nx = nxNEW; ny = nyNEW; nz = nzNEW;
            thee->gxcf[IJKx(j,k,2)] = 0.0;
            nx = nxNEW; ny = nyNEW; nz = nzNEW;
            thee->gxcf[IJKx(j,k,3)] = 0.0;
        }
    }

    /* Fill the "j" boundaries (dirichlet) */
    for (k=0; k<nzNEW; k++) {
        for (i=0; i<nxNEW; i++) {
            /* Low Y face */
            x = xminNEW + i*hxNEW;
            y = yminNEW;
            z = zminNEW + k*hzNEW;
            ifloat = (x - xminOLD)/hxOLD;
            jfloat = (y - yminOLD)/hyOLD;
            kfloat = (z - zminOLD)/hzOLD;
            ihi = (int)ceil(ifloat);
            if (ihi > (nxOLD-1)) ihi = nxOLD-1;
            ilo = (int)floor(ifloat);
            if (ilo < 0) ilo = 0;
            jhi = (int)ceil(jfloat);
            if (jhi > (nyOLD-1)) jhi = nyOLD-1;
            jlo = (int)floor(jfloat);
            if (jlo < 0) jlo = 0;
            khi = (int)ceil(kfloat);
            if (khi > (nzOLD-1)) khi = nzOLD-1;
            klo = (int)floor(kfloat);
            if (klo < 0) klo = 0;
            dx = ifloat - (double)(ilo);
            dy = jfloat - (double)(jlo);
            dz = kfloat - (double)(klo);
            nx = nxOLD; ny = nyOLD; nz = nzOLD;
            uval =  dx*dy*dz*(pmgOLD->u[IJK(ihi,jhi,khi)])
                  + dx*(1.0-dy)*dz*(pmgOLD->u[IJK(ihi,jlo,khi)])
                  + dx*dy*(1.0-dz)*(pmgOLD->u[IJK(ihi,jhi,klo)])
                  + dx*(1.0-dy)*(1.0-dz)*(pmgOLD->u[IJK(ihi,jlo,klo)])
                  + (1.0-dx)*dy*dz*(pmgOLD->u[IJK(ilo,jhi,khi)])
                  + (1.0-dx)*(1.0-dy)*dz*(pmgOLD->u[IJK(ilo,jlo,khi)])
                  + (1.0-dx)*dy*(1.0-dz)*(pmgOLD->u[IJK(ilo,jhi,klo)])
                  + (1.0-dx)*(1.0-dy)*(1.0-dz)*(pmgOLD->u[IJK(ilo,jlo,klo)]);
            nx = nxNEW; ny = nyNEW; nz = nzNEW;
            thee->gycf[IJKy(i,k,0)] = uval;

            /* High Y face */
            y = ymaxNEW;
            jfloat = (y - yminOLD)/hyOLD;
            jhi = (int)ceil(jfloat);
            if (jhi > (nyOLD-1)) jhi = nyOLD-1;
            jlo = (int)floor(jfloat);
            if (jlo < 0) jlo = 0;
            dy = jfloat - (double)(jlo);
            nx = nxOLD; ny = nyOLD; nz = nzOLD;
            uval =  dx*dy*dz*(pmgOLD->u[IJK(ihi,jhi,khi)])
                  + dx*(1.0-dy)*dz*(pmgOLD->u[IJK(ihi,jlo,khi)])
                  + dx*dy*(1.0-dz)*(pmgOLD->u[IJK(ihi,jhi,klo)])
                  + dx*(1.0-dy)*(1.0-dz)*(pmgOLD->u[IJK(ihi,jlo,klo)])
                  + (1.0-dx)*dy*dz*(pmgOLD->u[IJK(ilo,jhi,khi)])
                  + (1.0-dx)*(1.0-dy)*dz*(pmgOLD->u[IJK(ilo,jlo,khi)])
                  + (1.0-dx)*dy*(1.0-dz)*(pmgOLD->u[IJK(ilo,jhi,klo)])
                  + (1.0-dx)*(1.0-dy)*(1.0-dz)*(pmgOLD->u[IJK(ilo,jlo,klo)]);
            nx = nxNEW; ny = nyNEW; nz = nzNEW;
            thee->gycf[IJKy(i,k,1)] = uval;

            /* Zero Neumann conditions */
            nx = nxNEW; ny = nyNEW; nz = nzNEW;
            thee->gycf[IJKy(i,k,2)] = 0.0;
            nx = nxNEW; ny = nyNEW; nz = nzNEW;
            thee->gycf[IJKy(i,k,3)] = 0.0;
        }
    }

    /* Fill the "k" boundaries (dirichlet) */
    for (j=0; j<nyNEW; j++) {
        for (i=0; i<nxNEW; i++) {
            /* Low Z face */
            x = xminNEW + i*hxNEW;
            y = yminNEW + j*hyNEW;
            z = zminNEW;
            ifloat = (x - xminOLD)/hxOLD;
            jfloat = (y - yminOLD)/hyOLD;
            kfloat = (z - zminOLD)/hzOLD;
            ihi = (int)ceil(ifloat);
            if (ihi > (nxOLD-1)) ihi = nxOLD-1;
            ilo = (int)floor(ifloat);
            if (ilo < 0) ilo = 0;
            jhi = (int)ceil(jfloat);
            if (jhi > (nyOLD-1)) jhi = nyOLD-1;
            jlo = (int)floor(jfloat);
            if (jlo < 0) jlo = 0;
            khi = (int)ceil(kfloat);
            if (khi > (nzOLD-1)) khi = nzOLD-1;
            klo = (int)floor(kfloat);
            if (klo < 0) klo = 0;
            dx = ifloat - (double)(ilo);
            dy = jfloat - (double)(jlo);
            dz = kfloat - (double)(klo);
            nx = nxOLD; ny = nyOLD; nz = nzOLD;
            uval =  dx*dy*dz*(pmgOLD->u[IJK(ihi,jhi,khi)])
                  + dx*(1.0-dy)*dz*(pmgOLD->u[IJK(ihi,jlo,khi)])
                  + dx*dy*(1.0-dz)*(pmgOLD->u[IJK(ihi,jhi,klo)])
                  + dx*(1.0-dy)*(1.0-dz)*(pmgOLD->u[IJK(ihi,jlo,klo)])
                  + (1.0-dx)*dy*dz*(pmgOLD->u[IJK(ilo,jhi,khi)])
                  + (1.0-dx)*(1.0-dy)*dz*(pmgOLD->u[IJK(ilo,jlo,khi)])
                  + (1.0-dx)*dy*(1.0-dz)*(pmgOLD->u[IJK(ilo,jhi,klo)])
                  + (1.0-dx)*(1.0-dy)*(1.0-dz)*(pmgOLD->u[IJK(ilo,jlo,klo)]);
            nx = nxNEW; ny = nyNEW; nz = nzNEW;
            thee->gzcf[IJKz(i,j,0)] = uval;

            /* High Z face */
            z = zmaxNEW;
            kfloat = (z - zminOLD)/hzOLD;
            khi = (int)ceil(kfloat);
            if (khi > (nzOLD-1)) khi = nzOLD-1;
            klo = (int)floor(kfloat);
            if (klo < 0) klo = 0;
            dz = kfloat - (double)(klo);
            nx = nxOLD; ny = nyOLD; nz = nzOLD;
            uval =  dx*dy*dz*(pmgOLD->u[IJK(ihi,jhi,khi)])
                  + dx*(1.0-dy)*dz*(pmgOLD->u[IJK(ihi,jlo,khi)])
                  + dx*dy*(1.0-dz)*(pmgOLD->u[IJK(ihi,jhi,klo)])
                  + dx*(1.0-dy)*(1.0-dz)*(pmgOLD->u[IJK(ihi,jlo,klo)])
                  + (1.0-dx)*dy*dz*(pmgOLD->u[IJK(ilo,jhi,khi)])
                  + (1.0-dx)*(1.0-dy)*dz*(pmgOLD->u[IJK(ilo,jlo,khi)])
                  + (1.0-dx)*dy*(1.0-dz)*(pmgOLD->u[IJK(ilo,jhi,klo)])
                  + (1.0-dx)*(1.0-dy)*(1.0-dz)*(pmgOLD->u[IJK(ilo,jlo,klo)]);
            nx = nxNEW; ny = nyNEW; nz = nzNEW;
            thee->gzcf[IJKz(i,j,1)] = uval;

            /* Zero Neumann conditions */
            nx = nxNEW; ny = nyNEW; nz = nzNEW;
            thee->gzcf[IJKz(i,j,2)] = 0.0;
            nx = nxNEW; ny = nyNEW; nz = nzNEW;
            thee->gzcf[IJKz(i,j,3)] = 0.0;
        }
    }
}

/* ///////////////////////////////////////////////////////////////////////////
// Routine:  extEnergy
//
// Purpose:  Calculate energy from region outside of current (focused) domain
//
// Author:   Nathan Baker
/////////////////////////////////////////////////////////////////////////// */
VPRIVATE void extEnergy(Vpmg *thee, Vpmg *pmgOLD) {

    double hxNEW, hyNEW, hzNEW;
    double xminNEW, yminNEW, zminNEW;
    double xmaxNEW, ymaxNEW, zmaxNEW;
    int nxNEW, nyNEW, nzNEW;
    int nxOLD, nyOLD, nzOLD;
    int i;

    /* Set the new external energy contribution to zero.  Any external
     * contributions from higher levels will be included in the appropriate
     * energy function call. */
    thee->extEnergy = 0;

    /* New problem dimensions */
    hxNEW = thee->pmgp->hx;
    hyNEW = thee->pmgp->hy;
    hzNEW = thee->pmgp->hzed;
    nxNEW = thee->pmgp->nx;
    nyNEW = thee->pmgp->ny;
    nzNEW = thee->pmgp->nz;
    xminNEW = thee->pmgp->xcent - ((double)(nxNEW-1)*hxNEW)/2.0;
    xmaxNEW = thee->pmgp->xcent + ((double)(nxNEW-1)*hxNEW)/2.0;
    yminNEW = thee->pmgp->ycent - ((double)(nyNEW-1)*hyNEW)/2.0;
    ymaxNEW = thee->pmgp->ycent + ((double)(nyNEW-1)*hyNEW)/2.0;
    zminNEW = thee->pmgp->zcent - ((double)(nzNEW-1)*hzNEW)/2.0;
    zmaxNEW = thee->pmgp->zcent + ((double)(nzNEW-1)*hzNEW)/2.0;

    /* Old problem dimensions */
    nxOLD = pmgOLD->pmgp->nx;
    nyOLD = pmgOLD->pmgp->ny;
    nzOLD = pmgOLD->pmgp->nz;

    /* Create a partition based on the new problem dimensions */
    Vpmg_setPart(pmgOLD, xminNEW, yminNEW, zminNEW, xmaxNEW, ymaxNEW, zmaxNEW);
    /* Invert partition mask */
    for (i=0; i<(nxOLD*nyOLD*nzOLD); i++) 
      pmgOLD->pvec[i] = (!(pmgOLD->pvec[i]));
    /* Now calculate the energy on that subset of the domain */
    thee->extEnergy = Vpmg_energy(pmgOLD, 1);
    Vpmg_unsetPart(pmgOLD);
}

/* ///////////////////////////////////////////////////////////////////////////
// Routine:  bcCalc
//
// Purpose:  Dirichlet boundary function and initial approximation function.
//
// Args:     x    = position vector
//           flag = evaluation flag 
//                    0 => zero B.C.
//                    1 => single Debye-Huckel sphere
//                    2 => Debye-Huckel sphere for each atom
//                    4 => focusing
//
// Author:   Nathan Baker and Michael Holst
/////////////////////////////////////////////////////////////////////////// */
VPRIVATE double bcCalc(Vpbe *pbe, double x[], int flag) {

    double size, *position, charge, xkappa, eps_w, dist, T, val, pot;
    int i, iatom;
    Vatom *atom;
    Valist *alist;

    if (flag == 0) {
        return 0.0;
    } else if (flag == 1) {
        /* Get the solute radius in meters and position in angstroms */
        size = (1.0e-10)*Vpbe_getSoluteRadius(pbe);
        position = Vpbe_getSoluteCenter(pbe);

        /* We keep the charge relative to units of ec that are factored out;
         * this term should be dimensionless. The dielectric is unitless. */
        charge = Vunit_ec*Vpbe_getSoluteCharge(pbe);
        eps_w = Vpbe_getSolventDiel(pbe);

        /* Get xkappa in units of inverse meters */
        xkappa = (1.0e10)*Vpbe_getXkappa(pbe);

        /* The temperature is in units of K */
        T = Vpbe_getTemperature(pbe);

        /* Compute the distance (in units of m) */
        dist = 0;
        for (i=0; i<3; i++) dist += VSQR(position[i] - x[i]);
        dist = (1.0e-10)*VSQRT(dist);

        /* Compute the potential in J/electron */
        val = (charge)/(4*VPI*Vunit_eps0*eps_w*dist);
        if (xkappa != 0.0) val = val*(exp(-xkappa*(dist-size))/(1+xkappa*size));
        /* Scale the potential to be dimensionless */
        val = val*Vunit_ec/(Vunit_kb*T);
        return val;
    } else if (flag == 2) {
        pot = 0.0;
        eps_w = Vpbe_getSolventDiel(pbe);
        xkappa = (1.0e10)*Vpbe_getXkappa(pbe);
        T = Vpbe_getTemperature(pbe);
        alist = Vpbe_getValist(pbe);
        for (iatom=0; iatom<Valist_getNumberAtoms(alist); iatom++) {
            atom = Valist_getAtom(alist, iatom);
            position = Vatom_getPosition(atom);
            charge = Vatom_getCharge(atom);
            size = (1e-10)*Vatom_getRadius(atom);
            dist = 0;
            for (i=0; i<3; i++) dist += VSQR(position[i] - x[i]);
            dist = (1.0e-10)*VSQRT(dist);
            val = (charge)/(dist);
            if (xkappa != 0.0)
              val = val*(exp(-xkappa*(dist-size))/(1+xkappa*size));
            pot = pot + val;
        }

        return pot*(Vunit_ec*Vunit_ec)/(Vunit_kb*T*4*VPI*Vunit_eps0*eps_w);
    } else if (flag == 4) {
        Vnm_print(2, "VPMG::bcCalc -- not appropriate for focusing!\n");
        VASSERT(0);
    } else {
        Vnm_print(2, "VPMG::bcCalc -- invalid boundary condition flag (%d)!\n",
          flag);
        VASSERT(0);
    }

    return 0;
}


/* ///////////////////////////////////////////////////////////////////////////
// Routine:  Vpmg_ctor
//
// Purpose:  Construct the PMG object from scratch using the solver parameters
//           specifed by the passed Vpmgp object and the equation data from
//           the Vpbe object
//
// Author:   Nathan Baker
/////////////////////////////////////////////////////////////////////////// */
VPUBLIC Vpmg* Vpmg_ctor(Vpmgp *pmgp, Vpbe *pbe) {

    Vpmg *thee = VNULL;

    /* Set up the structure */
    thee = Vmem_malloc(VNULL, 1, sizeof(Vpmg) );
    VASSERT( thee != VNULL);
    VASSERT(Vpmg_ctor2(thee, pmgp, pbe));

    return thee;
}

/* ///////////////////////////////////////////////////////////////////////////
// Routine:  Vpmg_ctor2
//
// Purpose:  Construct the PMG object
//
// Notes:    See header files for default parameter values
//
// Author:   Nathan Baker
/////////////////////////////////////////////////////////////////////////// */
VPUBLIC int Vpmg_ctor2(Vpmg *thee, Vpmgp *pmgp, Vpbe *pbe) {

    int nxc, nyc, nzc, nf, nc, narrc, n_rpc, n_iz, n_ipc;

    /* Get the parameters */    
    VASSERT(pmgp != VNULL); 
    VASSERT(pbe != VNULL); 
    thee->pmgp = pmgp;
    thee->pbe = pbe;

    /* Set up the memory */
    thee->vmem = Vmem_ctor("APBS:VPMG");

    /* Calculate storage requirements */
    F77MGSZ(&(thee->pmgp->mgcoar), &(thee->pmgp->mgdisc), &(thee->pmgp->mgsolv),
      &(thee->pmgp->nx), &(thee->pmgp->ny), &(thee->pmgp->nz),
      &(thee->pmgp->nlev), &nxc, &nyc, &nzc, &nf, &nc, &(thee->pmgp->narr),
      &narrc, &n_rpc, &n_iz, &n_ipc, &(thee->pmgp->nrwk), &(thee->pmgp->niwk));

    /* If nonlinear & newton, then we need some additional storage */
    if ((thee->pmgp->nonlin == 1) && (thee->pmgp->meth == 1)) {
        thee->pmgp->nrwk += (2*nf);
    }

    Vnm_print(0, "Vpmg_ctor2: PMG chose nx = %d, ny = %d, nz = %d, nlev = %d\n",
      thee->pmgp->nx, thee->pmgp->ny, thee->pmgp->nz, thee->pmgp->nlev);

    /* Allocate storage */
    thee->iparm = (int *)Vmem_malloc(thee->vmem, 100, sizeof(int));
    thee->rparm = (double *)Vmem_malloc(thee->vmem, 100, sizeof(double));
    thee->iwork = (int *)Vmem_malloc(thee->vmem, thee->pmgp->niwk, 
      sizeof(int));
    thee->rwork = (double *)Vmem_malloc(thee->vmem, thee->pmgp->nrwk, 
      sizeof(double));
    thee->a1cf = (double *)Vmem_malloc(thee->vmem, thee->pmgp->narr, 
      sizeof(double));
    thee->a2cf = (double *)Vmem_malloc(thee->vmem, thee->pmgp->narr, 
      sizeof(double));
    thee->a3cf = (double *)Vmem_malloc(thee->vmem, thee->pmgp->narr, 
      sizeof(double));
    thee->ccf = (double *)Vmem_malloc(thee->vmem, thee->pmgp->narr, 
      sizeof(double));
    thee->fcf = (double *)Vmem_malloc(thee->vmem, thee->pmgp->narr, 
      sizeof(double));
    thee->tcf = (double *)Vmem_malloc(thee->vmem, thee->pmgp->narr, 
      sizeof(double));
    thee->u = (double *)Vmem_malloc(thee->vmem, thee->pmgp->narr, 
      sizeof(double));
    thee->xf = (double *)Vmem_malloc(thee->vmem, 5*(thee->pmgp->nx), 
      sizeof(double));
    thee->yf = (double *)Vmem_malloc(thee->vmem, 5*(thee->pmgp->ny), 
      sizeof(double));
    thee->zf = (double *)Vmem_malloc(thee->vmem, 5*(thee->pmgp->nz), 
      sizeof(double));
    thee->gxcf = (double *)Vmem_malloc(thee->vmem, 
      10*(thee->pmgp->ny)*(thee->pmgp->nz), sizeof(double));
    thee->gycf = (double *)Vmem_malloc(thee->vmem, 
      10*(thee->pmgp->nx)*(thee->pmgp->nz), sizeof(double));
    thee->gzcf = (double *)Vmem_malloc(thee->vmem, 
      10*(thee->pmgp->nx)*(thee->pmgp->ny), sizeof(double));
    thee->pvec = (int *)Vmem_malloc(thee->vmem, 
      (thee->pmgp->nx)*(thee->pmgp->ny)*(thee->pmgp->nz), sizeof(int));

    /* Plop some of the parameters into the iparm and rparm arrays */
    F77PACKMG(thee->iparm, thee->rparm, &(thee->pmgp->nrwk), &(thee->pmgp->niwk),
      &(thee->pmgp->nx), &(thee->pmgp->ny), &(thee->pmgp->nz),
      &(thee->pmgp->nlev), &(thee->pmgp->nu1), &(thee->pmgp->nu2),
      &(thee->pmgp->mgkey), &(thee->pmgp->itmax), &(thee->pmgp->istop),
      &(thee->pmgp->ipcon), &(thee->pmgp->nonlin), &(thee->pmgp->mgsmoo),
      &(thee->pmgp->mgprol), &(thee->pmgp->mgcoar), &(thee->pmgp->mgsolv),
      &(thee->pmgp->mgdisc), &(thee->pmgp->iinfo), &(thee->pmgp->errtol),
      &(thee->pmgp->ipkey), &(thee->pmgp->omegal), &(thee->pmgp->omegan),
      &(thee->pmgp->irite), &(thee->pmgp->iperf));

    /* Turn off restriction of observable calculations to a specific 
     * partition */
    Vpmg_unsetPart(thee);

    /* Ignore external energy contributions */
    thee->extEnergy = 0;

    thee->filled = 0;

    return 1;
}

/* ///////////////////////////////////////////////////////////////////////////
// Routine:  Vpmg_ctorFocus
//
// Purpose:  Construct the PMG object by focusing.  In other words, use the
//           solution from the passed Vpmg object to set the boundary
//           conditions for the new Vpmg object.  IN THE PROCESS, THE OLD VPMG
//           OBJECT IS DESTROYED.  The solver parameters specifed by the passed
//           Vpmgp object and the equation data from the Vpbe object are also
//           used.
//
// Author:   Nathan Baker
/////////////////////////////////////////////////////////////////////////// */
VPUBLIC Vpmg* Vpmg_ctorFocus(Vpmgp *pmgp, Vpbe *pbe, Vpmg *pmgOLD) {

    Vpmg *thee = VNULL;

    /* Set up the structure */
    thee = Vmem_malloc(VNULL, 1, sizeof(Vpmg) );
    VASSERT( thee != VNULL);
    VASSERT(Vpmg_ctor2Focus(thee, pmgp, pbe, pmgOLD));

    return thee;
}

/* ///////////////////////////////////////////////////////////////////////////
// Routine:  Vpmg_ctor2Focus
//
// Purpose:  Construct the PMG object
//
// Notes:    See Vpmg_ctor2Focus description
//
// Author:   Nathan Baker
/////////////////////////////////////////////////////////////////////////// */
VPUBLIC int Vpmg_ctor2Focus(Vpmg *thee, Vpmgp *pmgp, Vpbe *pbe, Vpmg *pmgOLD) {

    int nxc, nyc, nzc, nf, nc, narrc, n_rpc, n_iz, n_ipc;

    /* Get the parameters */    
    VASSERT(pmgp != VNULL); 
    VASSERT(pbe != VNULL); 
    VASSERT(pmgOLD != VNULL); 
    thee->pmgp = pmgp;
    thee->pbe = pbe;

    /* Set up the memory */
    thee->vmem = Vmem_ctor("APBS:VPMG");

    /* Calculate storage requirements */
    F77MGSZ(&(thee->pmgp->mgcoar), &(thee->pmgp->mgdisc), &(thee->pmgp->mgsolv),
      &(thee->pmgp->nx), &(thee->pmgp->ny), &(thee->pmgp->nz),
      &(thee->pmgp->nlev), &nxc, &nyc, &nzc, &nf, &nc, &(thee->pmgp->narr),
      &narrc, &n_rpc, &n_iz, &n_ipc, &(thee->pmgp->nrwk), &(thee->pmgp->niwk));

    /* Overwrite any default or user-specified boundary condition arguments; we
     * are now committed to a calculation via focusing */
    if (thee->pmgp->bcfl != 4) {
        Vnm_print(2, "Vpmg_ctor2Focus: reset boundary condition flag to 4!\n");
        thee->pmgp->bcfl = 4;
    }

    /* Allocate storage for boundaries */
    thee->gxcf = (double *)Vmem_malloc(thee->vmem, 
      10*(thee->pmgp->ny)*(thee->pmgp->nz), sizeof(double));
    thee->gycf = (double *)Vmem_malloc(thee->vmem, 
      10*(thee->pmgp->nx)*(thee->pmgp->nz), sizeof(double));
    thee->gzcf = (double *)Vmem_malloc(thee->vmem, 
      10*(thee->pmgp->nx)*(thee->pmgp->ny), sizeof(double));

    /* Fill boundaries */
    focusFillBound(thee, pmgOLD);

    /* Calculate energetic contributions from region outside focusing domain */
    extEnergy(thee, pmgOLD);

    /* Destroy old Vpmg object */
    Vpmg_dtor(&pmgOLD);

    /* Allocate storage for everything else */
    thee->iparm = (int *)Vmem_malloc(thee->vmem, 100, sizeof(int));
    thee->rparm = (double *)Vmem_malloc(thee->vmem, 100, sizeof(double));
    thee->iwork = (int *)Vmem_malloc(thee->vmem, thee->pmgp->niwk, 
      sizeof(int));
    thee->rwork = (double *)Vmem_malloc(thee->vmem, thee->pmgp->nrwk, 
      sizeof(double));
    thee->a1cf = (double *)Vmem_malloc(thee->vmem, thee->pmgp->narr, 
      sizeof(double));
    thee->a2cf = (double *)Vmem_malloc(thee->vmem, thee->pmgp->narr, 
      sizeof(double));
    thee->a3cf = (double *)Vmem_malloc(thee->vmem, thee->pmgp->narr, 
      sizeof(double));
    thee->ccf = (double *)Vmem_malloc(thee->vmem, thee->pmgp->narr, 
      sizeof(double));
    thee->fcf = (double *)Vmem_malloc(thee->vmem, thee->pmgp->narr, 
      sizeof(double));
    thee->tcf = (double *)Vmem_malloc(thee->vmem, thee->pmgp->narr, 
      sizeof(double));
    thee->u = (double *)Vmem_malloc(thee->vmem, thee->pmgp->narr, 
      sizeof(double));
    thee->xf = (double *)Vmem_malloc(thee->vmem, 5*(thee->pmgp->nx), 
      sizeof(double));
    thee->yf = (double *)Vmem_malloc(thee->vmem, 5*(thee->pmgp->ny), 
      sizeof(double));
    thee->zf = (double *)Vmem_malloc(thee->vmem, 5*(thee->pmgp->nz), 
      sizeof(double));
    thee->pvec = (int *)Vmem_malloc(thee->vmem, 
      (thee->pmgp->nz)*(thee->pmgp->nx)*(thee->pmgp->ny), sizeof(int));

    /* Plop some of the parameters into the iparm and rparm arrays */
    F77PACKMG(thee->iparm, thee->rparm, &(thee->pmgp->nrwk), &(thee->pmgp->niwk),
      &(thee->pmgp->nx), &(thee->pmgp->ny), &(thee->pmgp->nz),
      &(thee->pmgp->nlev), &(thee->pmgp->nu1), &(thee->pmgp->nu2),
      &(thee->pmgp->mgkey), &(thee->pmgp->itmax), &(thee->pmgp->istop),
      &(thee->pmgp->ipcon), &(thee->pmgp->nonlin), &(thee->pmgp->mgsmoo),
      &(thee->pmgp->mgprol), &(thee->pmgp->mgcoar), &(thee->pmgp->mgsolv),
      &(thee->pmgp->mgdisc), &(thee->pmgp->iinfo), &(thee->pmgp->errtol),
      &(thee->pmgp->ipkey), &(thee->pmgp->omegal), &(thee->pmgp->omegan),
      &(thee->pmgp->irite), &(thee->pmgp->iperf));


    /* Turn off restriction of observable calculations to a specific 
     * partition */
    Vpmg_unsetPart(thee);

    thee->filled = 0;

    return 1;
}

/* ///////////////////////////////////////////////////////////////////////////
// Routine:  Vpmg_solve
//
// Purpose:  Solve the equation
//
// Author:   Nathan Baker
/////////////////////////////////////////////////////////////////////////// */
VPUBLIC void Vpmg_solve(Vpmg *thee) {

    switch(thee->pmgp->meth) {
        /* CGMG (linear) */
        case 0:
            F77CGMGDRIV(thee->iparm, thee->rparm, thee->iwork, thee->rwork,
              thee->u, thee->xf, thee->yf, thee->zf, thee->gxcf, thee->gycf,
              thee->gzcf, thee->a1cf, thee->a2cf, thee->a3cf, thee->ccf,
              thee->fcf, thee->tcf);
            break;
        /* Newton (nonlinear) */
        case 1:
            F77NEWDRIV(thee->iparm, thee->rparm, thee->iwork, thee->rwork, 
              thee->u, thee->xf, thee->yf, thee->zf, thee->gxcf, thee->gycf,
              thee->gzcf, thee->a1cf, thee->a2cf, thee->a3cf, thee->ccf, 
              thee->fcf, thee->tcf);
            break;
        /* MG (linear/nonlinear) */
        case 2:
	    F77MGDRIV(thee->iparm, thee->rparm, thee->iwork, thee->rwork,
	      thee->u, thee->xf, thee->yf, thee->zf, thee->gxcf, thee->gycf,
	      thee->gzcf, thee->a1cf, thee->a2cf, thee->a3cf, thee->ccf,
              thee->fcf, thee->tcf);
            break;
        /* CGHS (linear/nonlinear) */
        case 3: 
	    F77NCGHSDRIV(thee->iparm, thee->rparm, thee->iwork, thee->rwork,
	      thee->u, thee->xf, thee->yf, thee->zf, thee->gxcf, thee->gycf,
	      thee->gzcf, thee->a1cf, thee->a2cf, thee->a3cf, thee->ccf,
              thee->fcf, thee->tcf);
            break;
        /* SOR (linear/nonlinear) */
        case 4:
	    F77NSORDRIV(thee->iparm, thee->rparm, thee->iwork, thee->rwork,
	      thee->u, thee->xf, thee->yf, thee->zf, thee->gxcf, thee->gycf,
	      thee->gzcf, thee->a1cf, thee->a2cf, thee->a3cf, thee->ccf,
              thee->fcf, thee->tcf);
            break;
        /* GSRB (linear/nonlinear) */
        case 5:
	    F77NGSRBDRIV(thee->iparm, thee->rparm, thee->iwork, thee->rwork,
	      thee->u, thee->xf, thee->yf, thee->zf, thee->gxcf, thee->gycf,
	      thee->gzcf, thee->a1cf, thee->a2cf, thee->a3cf, thee->ccf,
              thee->fcf, thee->tcf); 
            break;
        /* WJAC (linear/nonlinear) */
        case 6:
	    F77NWJACDRIV(thee->iparm, thee->rparm, thee->iwork, thee->rwork,
	      thee->u, thee->xf, thee->yf, thee->zf, thee->gxcf, thee->gycf,
	      thee->gzcf, thee->a1cf, thee->a2cf, thee->a3cf, thee->ccf,
              thee->fcf, thee->tcf);
            break;
        /* RICH (linear/nonlinear) */
        case 7:
	    F77NRICHDRIV(thee->iparm, thee->rparm, thee->iwork, thee->rwork,
	      thee->u, thee->xf, thee->yf, thee->zf, thee->gxcf, thee->gycf,
	      thee->gzcf, thee->a1cf, thee->a2cf, thee->a3cf, thee->ccf,
              thee->fcf, thee->tcf);
            break;
        /* Error handling */
        default: 
            Vnm_print(2, "Vpgm_solve: invalid solver method key (%d)\n",
              thee->pmgp->key);
            break;
    }

}

/* ///////////////////////////////////////////////////////////////////////////
// Routine:  Vpmg_fillco
//
// Purpose:  Fill the coefficient arrays prior to solving the equation
//
// Args:     epsmeth  The method to use to generate discretizations of the 
//                    dielectric functions:
//                       0 => straight discretization (collocation-like), no
//                            smoothing
//                       1 => smoothing based on a harmonic average of the
//                            value at three points
//           epsparm  Parameter for dielectric discretizing functions
//
// Author:   Nathan Baker
/////////////////////////////////////////////////////////////////////////// */
VPUBLIC void Vpmg_fillco(Vpmg *thee, int epsmeth, double epsparm) {

    Vacc *acc;
    Valist *alist;
    Vpbe *pbe;
    Vatom *atom;
    double xmin, xmax, ymin, ymax, zmin, zmax;
    double xlen, ylen, zlen, position[3], ifloat, jfloat, kfloat, accf;
    double zmagic, irad, srad, charge, dx, dy, dz, zkappa2, epsw, epsp;
    double hx, hy, hzed, *apos, arad;
    int i, j, k, nx, ny, nz, iatom, ihi, ilo, jhi, jlo, khi, klo;
    int imin, imax, jmin, jmax, kmin, kmax;
    double dx2, dy2, dz2, arad2, stot2, itot2, rtot, rtot2;
    int acclo, accmid, acchi, a000;


    /* Get PBE info */
    pbe = thee->pbe;
    acc = pbe->acc;
    alist = pbe->alist;
    irad = Vpbe_getIonRadius(pbe);
    srad = Vpbe_getSolventRadius(pbe);
    zmagic = Vpbe_getZmagic(pbe);
    zkappa2 = Vpbe_getZkappa2(pbe);
    epsw = Vpbe_getSolventDiel(pbe);
    epsp = Vpbe_getSoluteDiel(pbe);

    /* Mesh info */
    nx = thee->pmgp->nx;
    ny = thee->pmgp->ny;
    nz = thee->pmgp->nz;
    hx = thee->pmgp->hx;
    hy = thee->pmgp->hy;
    hzed = thee->pmgp->hzed;
   
    /* Define the total domain size */
    xlen = hx*(nx - 1);
    ylen = hy*(ny - 1);
    zlen = hzed*(nz - 1);

    /* Define the min/max dimensions */
    xmin = thee->pmgp->xcent - (xlen/2.0);
    ymin = thee->pmgp->ycent - (ylen/2.0);
    zmin = thee->pmgp->zcent - (zlen/2.0);
    xmax = thee->pmgp->xcent + (xlen/2.0);
    ymax = thee->pmgp->ycent + (ylen/2.0);
    zmax = thee->pmgp->zcent + (zlen/2.0);
    thee->rparm[2] = xmin;
    thee->rparm[3] = xmax;
    thee->rparm[4] = ymin;
    thee->rparm[5] = ymax;
    thee->rparm[6] = zmin;
    thee->rparm[7] = zmax;

    /* Fill the mesh point coordinate arrays */
    for (i=0; i<nx; i++) thee->xf[i] = xmin + i*hx;
    for (i=0; i<ny; i++) thee->yf[i] = ymin + i*hy;
    for (i=0; i<nz; i++) thee->zf[i] = zmin + i*hzed;

    /* Reset the fcf, tcf, ccf, a1cf, a2cf, and a3cf arrays */
    for (i=0; i<(nx*ny*nz); i++) {
        thee->tcf[i] = 0.0;
        thee->fcf[i] = 0.0;
        thee->ccf[i] = 0.0;
        thee->a1cf[i] = 0.0;
        thee->a2cf[i] = 0.0;
        thee->a3cf[i] = 0.0;
    }

    /* Loop through the atoms and do the following:
     * 1.  Set ccf = -1.0 for all points inside the inflated van der Waals
     *     radii
     * 2.  Set a{123}cf = -1.0 if a point is inside the inflated van der Waals
     *     radii
     * 3.  Set a{123}cf = -2.0 if a point is inside the van der Waals radii
     * 4.  Fill in the source term array
     */
    /* Fill source term array */
    for (iatom=0; iatom<Valist_getNumberAtoms(alist); iatom++) {

        atom = Valist_getAtom(alist, iatom);
        apos = Vatom_getPosition(atom);
        arad = Vatom_getRadius(atom);
        charge = Vatom_getCharge(atom);

        /* Make sure we're on the grid */
        if ((apos[0]<=xmin) || (apos[0]>=xmax)  || \
            (apos[1]<=ymin) || (apos[1]>=ymax)  || \
            (apos[2]<=zmin) || (apos[2]>=zmax)) {
            if (thee->pmgp->bcfl != 4) {
                Vnm_print(2, "Vpmg_fillco:  Atom #%d at (%4.3f, %4.3f, %4.3f) is off the mesh (ignoring):\n",
                  iatom, position[0], position[1], position[2]);
                Vnm_print(2, "Vpmg_fillco:    xmin = %g, xmax = %g\n", 
                  xmin, xmax);
                Vnm_print(2, "Vpmg_fillco:    ymin = %g, ymax = %g\n", 
                  ymin, ymax);
                Vnm_print(2, "Vpmg_fillco:    zmin = %g, zmax = %g\n", 
                  zmin, zmax);
            }
            fflush(stderr);
        } else {

            /* Convert the atom position to grid reference frame */
            position[0] = apos[0] - xmin;
            position[1] = apos[1] - ymin;
            position[2] = apos[2] - zmin;

            /* MARK ION ACCESSIBILITY AND DIELECTRIC VALUES FOR LATER
             * ASSIGNMENT (Steps #1-3) */
            itot2 = VSQR(irad + arad);     
            stot2 = VSQR(srad + arad);
            arad2 = VSQR(arad);
            /* We'll search over grid points which are in the greater of these
             * two radii */
            rtot = VMAX2((irad + arad), (srad + arad));
            rtot2 = VMAX2(itot2, stot2);
            dx = rtot + 0.5*hx;
            imin = VMAX2(0,(int)ceil((position[0] - dx)/hx));
            imax = VMIN2(nx-1,(int)floor((position[0] + dx)/hx));
            for (i=imin; i<=imax; i++) {
                dx2 = VSQR(position[0] - hx*i);
                if (rtot2 > dx2) dy = VSQRT(rtot2 - dx2) + 0.5*hy;
                else dy = 0.5*hy;
                jmin = VMAX2(0,(int)ceil((position[1] - dy)/hy));
                jmax = VMIN2(ny-1,(int)floor((position[1] + dy)/hy));
                for (j=jmin; j<=jmax; j++) {
                    dy2 = VSQR(position[1] - hy*j);
                    if (rtot2 > (dx2+dy2)) dz = VSQRT(rtot2-dx2-dy2)+0.5*hzed;
                    else dz = 0.5*hzed;
                    kmin = VMAX2(0,(int)ceil((position[2] - dz)/hzed));
                    kmax = VMIN2(nz-1,(int)floor((position[2] + dz)/hzed));
                    for (k=kmin; k<=kmax; k++) {
                        dz2 = VSQR(k*hzed - position[2]);
                        /* See if grid point is inside ivdw radius and set ccf
                         * accordingly */
                        if ((dz2 + dy2 + dx2) <= itot2) 
                          thee->ccf[IJK(i,j,k)] = -1.0;
                        /* See if x-shifted grid point is inside ivdw rad. */
                        if ((dz2+dy2+VSQR((i+0.5)*hx-position[0]))<=stot2) {
                            /* See if inside vdw rad */
                            if ((dz2+dy2+VSQR((i+0.5)*hx-position[0]))<=arad2) 
                              thee->a1cf[IJK(i,j,k)] = -2.0;
                            else thee->a1cf[IJK(i,j,k)] = -1.0;
                        } 
                        /* See if y-shifted grid point is inside ivdw rad. */
                        if ((dz2+VSQR((j+0.5)*hy-position[1])+dx2) <= stot2) {
                            /* See if inside vdw rad */
                            if ((dz2+VSQR((j+0.5)*hy-position[1])+dx2)<=arad2) 
                              thee->a2cf[IJK(i,j,k)] = -2.0;
                            else thee->a2cf[IJK(i,j,k)] = -1.0;
                        }        
                        /* See if z-shifted grid point is inside ivdw rad. */
                        if ((VSQR((k+0.5)*hzed-position[2])+dy2+dx2)<=stot2) {
                            /* See if inside vdw rad */
                            if ((VSQR((k+0.5)*hzed-position[2])+dy2+dx2)<=arad2)
                              thee->a3cf[IJK(i,j,k)] = -2.0;
                            else thee->a3cf[IJK(i,j,k)] = -1.0;
                        }        
                    } /* k loop */
                } /* j loop */
            } /* i loop */

            /* FILL IN SOURCE TERM ARRAY */
            /* Scale the charge to be a delta function */
            charge = charge*zmagic/(hx*hy*hzed);

            /* Figure out which vertices we're next to */
            ifloat = position[0]/hx;
            jfloat = position[1]/hy;
            kfloat = position[2]/hzed;

            ihi = (int)ceil(ifloat);
            ilo = (int)floor(ifloat);
            jhi = (int)ceil(jfloat);
            jlo = (int)floor(jfloat);
            khi = (int)ceil(kfloat);
            klo = (int)floor(kfloat);

            /* Now assign fractions of the charge to the nearby verts */
            dx = ifloat - (double)(ilo);
            dy = jfloat - (double)(jlo);
            dz = kfloat - (double)(klo);
            thee->fcf[IJK(ihi,jhi,khi)] += (dx*dy*dz*charge);
            thee->fcf[IJK(ihi,jlo,khi)] += (dx*(1.0-dy)*dz*charge);
            thee->fcf[IJK(ihi,jhi,klo)] += (dx*dy*(1.0-dz)*charge);
            thee->fcf[IJK(ihi,jlo,klo)] += (dx*(1.0-dy)*(1.0-dz)*charge);
            thee->fcf[IJK(ilo,jhi,khi)] += ((1.0-dx)*dy*dz*charge);
            thee->fcf[IJK(ilo,jlo,khi)] += ((1.0-dx)*(1.0-dy)*dz*charge);
            thee->fcf[IJK(ilo,jhi,klo)] += ((1.0-dx)*dy*(1.0-dz)*charge);
            thee->fcf[IJK(ilo,jlo,klo)] += ((1.0-dx)*(1.0-dy)*(1.0-dz)*charge);

        }
    }

    /* Interpret markings and fill the coefficient arrays */
    for (k=0; k<nz; k++) {
        for (j=0; j<ny; j++) {
            for (i=0; i<nx; i++) {

                position[0] = thee->xf[i];
                position[1] = thee->yf[j];
                position[2] = thee->zf[k];

                /* the scalar (0th derivative) entry */
                if (thee->ccf[IJK(i,j,k)] == -1.0)
                  thee->ccf[IJK(i,j,k)] = 0.0;
                else thee->ccf[IJK(i,j,k)] = zkappa2;

                /* The diagonal tensor (2nd derivative) entries.  Each of these
                 * entries is evaluated ad the grid edges midpoints.  */
                switch (epsmeth) {

                  /* No dielectric smoothing */
                  case 0: 
                    /* x-direction */
                    if (thee->a1cf[IJK(i,j,k)] == -1.0) {
                        position[0] = thee->xf[i] + 0.5*hx;
                        position[1] = thee->yf[j];
                        position[2] = thee->zf[k];
                        if (Vacc_molAcc(acc, position, srad) == 0) 
                          thee->a1cf[IJK(i,j,k)] = epsp; 
                        else thee->a1cf[IJK(i,j,k)] = epsw; 
                    }
                    /* y-direction */
                    if (thee->a2cf[IJK(i,j,k)] == -1.0) {
                        position[0] = thee->xf[i];
                        position[1] = thee->yf[j] + 0.5*hy;
                        position[2] = thee->zf[k];
                        if (Vacc_molAcc(acc, position, srad) == 0) 
                          thee->a2cf[IJK(i,j,k)] = epsp; 
                        else thee->a2cf[IJK(i,j,k)] = epsw; 
                    }
                    /* z-direction */
                    if (thee->a3cf[IJK(i,j,k)] == -1.0) {
                        position[0] = thee->xf[i];
                        position[1] = thee->yf[j];
                        position[2] = thee->zf[k] + 0.5*hzed;
                        if (Vacc_molAcc(acc, position, srad) == 0) 
                          thee->a3cf[IJK(i,j,k)] = epsp; 
                        else thee->a3cf[IJK(i,j,k)] = epsw; 
                    }
                    break; 

                  /* A very rudimentary form of dielectric smoothing.
                   * Specifically, the dielectric will be evaluated at the mid
		   * point and the two flanking mesh points.  The fraction of
		   * the grid edge in the solvent will then be calculated from
		   * these three values (i.e., either 0, 1/3, 2/3, or 1).  The
		   * dielectric value at the midpoint will then be assigned
		   * based on the usual dielectric smoothing formula:
		   * \epsilon_s\epsilon_i/(a\epsilon_s + (1-a)\epsilon_i)  */
                  case 1:
                    if ((thee->a1cf[IJK(i,j,k)] == -1.0) ||
                        (thee->a2cf[IJK(i,j,k)] == -1.0) ||
                        (thee->a3cf[IJK(i,j,k)] == -1.0)) {
                        position[0] = thee->xf[i];
                        position[1] = thee->yf[j];
                        position[2] = thee->zf[k];
                        a000 = Vacc_molAcc(acc, position, srad);
                    }
                    /* x-direction */
                    if (thee->a1cf[IJK(i,j,k)] == -1.0) {
                        position[0] = thee->xf[i] + 0.5*hx;
                        position[1] = thee->yf[j];
                        position[2] = thee->zf[k];
                        acclo = a000;
                        accmid = Vacc_molAcc(acc, position, srad);
                        position[0] = thee->xf[i] + hx;
                        acchi = Vacc_molAcc(acc, position, srad);
                        accf = ((double)acchi+(double)accmid+(double)acclo)/3.0;
                        thee->a1cf[IJK(i,j,k)] = 
                          epsw*epsp/((1-accf)*epsw + accf*epsp);
                    }
                    /* y-direction */
                    if (thee->a2cf[IJK(i,j,k)] == -1.0) {
                        position[0] = thee->xf[i];
                        position[1] = thee->yf[j] + 0.5*hy;
                        position[2] = thee->zf[k];
                        accmid = Vacc_molAcc(acc, position, srad);
                        acclo = a000;
                        position[1] = thee->yf[j] + hy;
                        acchi = Vacc_molAcc(acc, position, srad);
                        accf = ((double)acchi+(double)accmid+(double)acclo)/3.0;
                        thee->a2cf[IJK(i,j,k)] = 
                          epsw*epsp/((1-accf)*epsw + accf*epsp);
                    }
                    /* z-direction */
                    if (thee->a3cf[IJK(i,j,k)] == -1.0) {
                        position[0] = thee->xf[i];
                        position[1] = thee->yf[j];
                        position[2] = thee->zf[k] + 0.5*hzed;
                        accmid = Vacc_molAcc(acc, position, srad);
                        acclo = a000;
                        position[2] = thee->zf[k] + hzed;
                        acchi = Vacc_molAcc(acc, position, srad);
                        accf = ((double)acchi+(double)accmid+(double)acclo)/3.0;
                        thee->a3cf[IJK(i,j,k)] = 
                          epsw*epsp/((1-accf)*epsw + accf*epsp);
                    }
                    break;

                  /* Oops, invalid epsmeth */
                  default:
                    Vnm_print(2, "Vpmg_fillco:  Bad epsmeth (%d)!\n", epsmeth);
                    VASSERT(0);
                }
                /* Fill in the remaining dielectric values */
                if (thee->a1cf[IJK(i,j,k)] == -2.0)
                  thee->a1cf[IJK(i,j,k)] = epsp;
                if (thee->a2cf[IJK(i,j,k)] == -2.0)
                  thee->a2cf[IJK(i,j,k)] = epsp;
                if (thee->a3cf[IJK(i,j,k)] == -2.0)
                  thee->a3cf[IJK(i,j,k)] = epsp;
                if (thee->a1cf[IJK(i,j,k)] == 0.0)
                  thee->a1cf[IJK(i,j,k)] = epsw;
                if (thee->a2cf[IJK(i,j,k)] == 0.0)
                  thee->a2cf[IJK(i,j,k)] = epsw;
                if (thee->a3cf[IJK(i,j,k)] == 0.0)
                  thee->a3cf[IJK(i,j,k)] = epsw;
            }
        }
    }

    /* Fill the boundary arrays (except when focusing, bcfl = 4) */
    if (thee->pmgp->bcfl != 4) {
        /* the "i" boundaries (dirichlet) */
        for (k=0; k<nz; k++) {
            for (j=0; j<ny; j++) {
                position[0] = thee->xf[0];
                position[1] = thee->yf[j];
                position[2] = thee->zf[k];
                thee->gxcf[IJKx(j,k,0)] = bcCalc(pbe, position, 
                  thee->pmgp->bcfl);
                position[0] = thee->xf[nx-1];
                thee->gxcf[IJKx(j,k,1)] = bcCalc(pbe, position, 
                  thee->pmgp->bcfl);
                thee->gxcf[IJKx(j,k,2)] = 0.0;
                thee->gxcf[IJKx(j,k,3)] = 0.0;
            }
        }

        /* the "j" boundaries (dirichlet) */
        for (k=0; k<nz; k++) {
            for (i=0; i<nx; i++) {
                position[0] = thee->xf[i];
                position[1] = thee->yf[0];
                position[2] = thee->zf[k];
                thee->gycf[IJKy(i,k,0)] = bcCalc(pbe, position, 
                  thee->pmgp->bcfl);
                position[1] = thee->yf[ny-1];
                thee->gycf[IJKy(i,k,1)] = bcCalc(pbe, position, 
                  thee->pmgp->bcfl);
                thee->gycf[IJKy(i,k,2)] = 0.0;
                thee->gycf[IJKy(i,k,3)] = 0.0;
            }
        }

        /* the "k" boundaries (dirichlet) */
        for (j=0; j<ny; j++) {
            for (i=0; i<nx; i++) {
                position[0] = thee->xf[i];
                position[1] = thee->yf[j];
                position[2] = thee->zf[0];
                thee->gzcf[IJKz(i,j,0)] = bcCalc(pbe, position, 
                  thee->pmgp->bcfl);
                position[2] = thee->zf[nz-1];
                thee->gzcf[IJKz(i,j,1)] = bcCalc(pbe, position, 
                  thee->pmgp->bcfl);
                thee->gzcf[IJKz(i,j,2)] = 0.0;
                thee->gzcf[IJKz(i,j,3)] = 0.0;
            }
        }
    }

    thee->filled = 1;
}

/* ///////////////////////////////////////////////////////////////////////////
// Routine:  Vpmg_energy
//
// Purpose:  Return the energy in units of $k_B T$.  
//
// Args:     extFlag => If this was a focused calculation, then it is possible
//                      to include the energy contributions from the outside
//                      the focused domain.  This should be on (=1) for
//                      sequential focusing calculations and off (=0) for
//                      parallel calculations.
//
// Author:   Nathan Baker
/////////////////////////////////////////////////////////////////////////// */
VPUBLIC double Vpmg_energy(Vpmg *thee, int extFlag) {

    double energy = 0.0;

    VASSERT(thee != VNULL);
    VASSERT(thee->filled);

    if (thee->pmgp->nonlin) {
        Vnm_print(2, "Vpmg_energy:  NPBE energy routines not implemented yet!\n");
        energy = 0.0;
    } else {
        energy = Vpmg_qfEnergy(thee);
        if (extFlag == 1) energy += (thee->extEnergy);
    }

    return energy;

}

/* ///////////////////////////////////////////////////////////////////////////
// Routine:  Vpmg_dielEnergy
//
// Purpose:  Using the solution at the finest mesh level, get the electrostatic
//           energy due to the interaction of the mobile charges with the
//           potential:  
//             \[ G = -\frac{1}{2} \int \epsilon (\nabla u)^2 dx \].
//           and return the result in units of $k_B T$.  Clearly, no
//           self-interaction terms are removed.
//
// Notes:    The value of this observable may be modified by setting
//           restrictions on the subdomain over which it is calculated.  Such
//           limits can be set via Vpmg_setPart and are generally useful for
//           parallel runs.
//
// Author:   Nathan Baker
/////////////////////////////////////////////////////////////////////////// */
VPUBLIC double Vpmg_dielEnergy(Vpmg *thee) {

    double hx, hy, hzed, energy, nrgx, nrgy, nrgz, T, pvecx, pvecy, pvecz;
    int i, j, k, nx, ny, nz;
 
    VASSERT(thee != VNULL);
    VASSERT(thee->filled);

    /* Get the mesh information */
    nx = thee->pmgp->nx;
    ny = thee->pmgp->ny;
    nz = thee->pmgp->nz;
    hx = thee->pmgp->hx;
    hy = thee->pmgp->hy;
    hzed = thee->pmgp->hzed;

    energy = 0.0;

    /* Refill the dieletric coefficient arrays */
    Vpmg_fillco(thee, 1, 0);

    for (k=0; k<(nz-1); k++) {
        for (j=0; j<(ny-1); j++) {
            for (i=0; i<(nx-1); i++) {
                pvecx = 0.5*(thee->pvec[IJK(i,j,k)]+thee->pvec[IJK(i+1,j,k)]);
                pvecy = 0.5*(thee->pvec[IJK(i,j,k)]+thee->pvec[IJK(i,j+1,k)]);
                pvecz = 0.5*(thee->pvec[IJK(i,j,k)]+thee->pvec[IJK(i,j,k+1)]);
                nrgx = thee->a1cf[IJK(i,j,k)]*pvecx
                  * VSQR((thee->u[IJK(i,j,k)]-thee->u[IJK(i+1,j,k)])/hx);
                nrgy = thee->a2cf[IJK(i,j,k)]*pvecy
                  * VSQR((thee->u[IJK(i,j,k)]-thee->u[IJK(i,j+1,k)])/hy);
                nrgz = thee->a3cf[IJK(i,j,k)]*pvecz
                  * VSQR((thee->u[IJK(i,j,k)]-thee->u[IJK(i,j,k+1)])/hzed);
                energy += (nrgx + nrgy + nrgz);
            }
        }
    }

    energy = 0.5*energy*hx*hy*hzed;
    T = Vpbe_getTemperature(thee->pbe);
    energy = energy/Vpbe_getZmagic(thee->pbe);

    return energy;
}

/* ///////////////////////////////////////////////////////////////////////////
// Routine:  Vpmg_qmEnergy
//
// Purpose:  Using the solution at the finest mesh level, get the electrostatic
//           energy due to the interaction of the mobile charges with the
//           potential.  For the NPBE, this is
//             \[ G = -\int \kappa^2(\cosh u - 1) dx \]
//           while for the LPBE it is
//             \[ G = -\frac{1}{2} \kappa^2 \int u^2 dx \]
//           and return the result in units of $k_B T$.  Clearly, no
//           self-interaction terms are removed.
//
// Notes:    The value of this observable may be modified by setting
//           restrictions on the subdomain over which it is calculated.  Such
//           limits can be set via Vpmg_setPart and are generally useful for
//           parallel runs.
//
// Author:   Nathan Baker
/////////////////////////////////////////////////////////////////////////// */
VPUBLIC double Vpmg_qmEnergy(Vpmg *thee) {

    double hx, hy, hzed, energy;
    int i, nx, ny, nz;
 
    VASSERT(thee != VNULL);
    VASSERT(thee->filled);

    /* Get the mesh information */
    nx = thee->pmgp->nx;
    ny = thee->pmgp->ny;
    nz = thee->pmgp->nz;
    hx = thee->pmgp->hx;
    hy = thee->pmgp->hy;
    hzed = thee->pmgp->hzed;

    energy = 0.0;

    if (thee->pmgp->nonlin) {
        Vnm_print(0, "Vpmg_qmEnergy:  Calculating nonlinear energy\n");
        for (i=0; i<(nx*ny*nz); i++) {
            /* Avoid problems with the cosh */
            if (thee->pvec[i]*thee->ccf[i] > 0) 
              energy += (thee->pvec[i]*thee->ccf[i]*(VCOSH(thee->u[i])-1.0));
        }
    } else {
        Vnm_print(0, "Vpmg_qmEnergy:  Calculating linear energy\n");
        for (i=0; i<(nx*ny*nz); i++) {
            /* Avoid problems with large potential values */
            if (thee->pvec[i]*thee->ccf[i] > 0) 
              energy += (thee->pvec[i]*thee->ccf[i]*VSQR(thee->u[i]));
        }
        energy = 0.5*energy;
    }
    energy = -1.0*energy*hx*hy*hzed;

    return energy;
}
    
/* ///////////////////////////////////////////////////////////////////////////
// Routine:  Vpmg_qfEnergy
//
// Purpose:  Using the solution at the finest mesh level, get the electrostatic
//           energy due to the interaction of the fixed charges with the
//           potential: 
//             \[ G = \frac{1}{2} \sum_i q_i u(r_i) \]
//           and return the result in units of $k_B T$.  Clearly, no
//           self-interaction terms are removed.
//
// Args:     extFlag => If this was a focused calculation, then it is possible
//                      to include the energy contributions from the outside
//                      the focused domain.  This should be on (=1) for
//                      sequential focusing calculations and off (=0) for
//                      parallel calculations.
//     
// Notes:    The value of this observable may be modified by setting
//           restrictions on the subdomain over which it is calculated.  Such
//           limits can be set via Vpmg_setPart and are generally useful for
//           parallel runs.  
//
// Author:   Nathan Baker
/////////////////////////////////////////////////////////////////////////// */
VPUBLIC double Vpmg_qfEnergy(Vpmg *thee) {

    int iatom, nx, ny, nz, ihi, ilo, jhi, jlo, khi, klo;
    double xmax, xmin, ymax, ymin, zmax, zmin, hx, hy, hzed, ifloat, jfloat;
    double charge, kfloat, dx, dy, dz, energy, uval, *position;
    double *u;
    int *pvec;
    Valist *alist;
    Vatom *atom; 
    Vpbe *pbe;

    pbe = thee->pbe;
    alist = pbe->alist;
    VASSERT(alist != VNULL);

    /* Get the mesh information */
    nx = thee->pmgp->nx;
    ny = thee->pmgp->ny;
    nz = thee->pmgp->nz;
    hx = thee->pmgp->hx;
    hy = thee->pmgp->hy;
    hzed = thee->pmgp->hzed;
    xmax = thee->xf[nx-1];
    ymax = thee->yf[ny-1];
    zmax = thee->zf[nz-1];
    xmin = thee->xf[0];
    ymin = thee->yf[0];
    zmin = thee->zf[0];

    u = thee->u;
    pvec = thee->pvec;
  
    energy = 0.0;

    for (iatom=0; iatom<Valist_getNumberAtoms(alist); iatom++) {
        /* Get atomic information */
        atom = Valist_getAtom(alist, iatom);

        position = Vatom_getPosition(atom);
        charge = Vatom_getCharge(atom);

        /* Figure out which vertices we're next to */
        ifloat = (position[0] - xmin)/hx;
        jfloat = (position[1] - ymin)/hy;
        kfloat = (position[2] - zmin)/hzed;
        ihi = (int)ceil(ifloat);
        ilo = (int)floor(ifloat);
        jhi = (int)ceil(jfloat);
        jlo = (int)floor(jfloat);
        khi = (int)ceil(kfloat);
        klo = (int)floor(kfloat);

        if ((ihi<nx) && (jhi<ny) && (khi<nz) &&
            (ilo>=0) && (jlo>=0) && (klo>=0)) {

            /* Now get trilinear interpolation constants */
            dx = ifloat - (double)(ilo);
            dy = jfloat - (double)(jlo);
            dz = kfloat - (double)(klo);
            uval =  
              dx*dy*dz
               *(u[IJK(ihi,jhi,khi)]*(double)(pvec[IJK(ihi,jhi,khi)]))
            + dx*(1.0-dy)*dz
               *(u[IJK(ihi,jlo,khi)]*(double)(pvec[IJK(ihi,jlo,khi)]))
            + dx*dy*(1.0-dz)
               *(u[IJK(ihi,jhi,klo)]*(double)(pvec[IJK(ihi,jhi,klo)]))
            + dx*(1.0-dy)*(1.0-dz)
               *(u[IJK(ihi,jlo,klo)]*(double)(pvec[IJK(ihi,jlo,klo)]))
            + (1.0-dx)*dy*dz
               *(u[IJK(ilo,jhi,khi)]*(double)(pvec[IJK(ilo,jhi,khi)]))
            + (1.0-dx)*(1.0-dy)*dz
               *(u[IJK(ilo,jlo,khi)]*(double)(pvec[IJK(ilo,jlo,khi)]))
            + (1.0-dx)*dy*(1.0-dz)
               *(u[IJK(ilo,jhi,klo)]*(double)(pvec[IJK(ilo,jhi,klo)]))
            + (1.0-dx)*(1.0-dy)*(1.0-dz)
               *(u[IJK(ilo,jlo,klo)]*(double)(pvec[IJK(ilo,jlo,klo)]));
            energy += (uval*charge);
        } else if (thee->pmgp->bcfl != 4) {
            Vnm_print(2, "Vpmg_qfEnergy:  Atom #%d at (%4.3f, %4.3f, %4.3f) is off the mesh (ignoring)!\n",
                iatom, position[0], position[1], position[2]);
        }
    }

    energy = 0.5*energy;
    return energy;
}
    
/* ///////////////////////////////////////////////////////////////////////////
// Routine:  Vpmg_dtor
//
// Purpose:  Clean up
//
// Author:   Nathan Baker
/////////////////////////////////////////////////////////////////////////// */
VPUBLIC void Vpmg_dtor(Vpmg **thee) {
    
    if ((*thee) != VNULL) {
        Vpmg_dtor2(*thee);
        Vmem_free(VNULL, 1, sizeof(Vpmg), (void **)thee);
        (*thee) = VNULL;
    }

}

/* ///////////////////////////////////////////////////////////////////////////
// Routine:  Vpmg_dtor2
//
// Purpose:  Clean up
//
// Author:   Nathan Baker
/////////////////////////////////////////////////////////////////////////// */
VPUBLIC void Vpmg_dtor2(Vpmg *thee) { 

    /* Clean up the storage */
    Vmem_free(thee->vmem, 100, sizeof(int), (void **)&(thee->iparm));
    Vmem_free(thee->vmem, 100, sizeof(double), (void **)&(thee->rparm));
    Vmem_free(thee->vmem, thee->pmgp->niwk, sizeof(int), 
      (void **)&(thee->iwork));
    Vmem_free(thee->vmem, thee->pmgp->nrwk, sizeof(double), 
      (void **)&(thee->rwork));
    Vmem_free(thee->vmem, thee->pmgp->narr, sizeof(double),
      (void **)&(thee->a1cf));
    Vmem_free(thee->vmem, thee->pmgp->narr, sizeof(double), 
      (void **)&(thee->a2cf));
    Vmem_free(thee->vmem, thee->pmgp->narr, sizeof(double),
      (void **)&(thee->a3cf));
    Vmem_free(thee->vmem, thee->pmgp->narr, sizeof(double),
      (void **)&(thee->ccf));
    Vmem_free(thee->vmem, thee->pmgp->narr, sizeof(double), 
      (void **)&(thee->fcf));
    Vmem_free(thee->vmem, thee->pmgp->narr, sizeof(double), 
      (void **)&(thee->tcf));
    Vmem_free(thee->vmem, thee->pmgp->narr, sizeof(double), 
      (void **)&(thee->u));
    Vmem_free(thee->vmem, 5*(thee->pmgp->nx), sizeof(double),
      (void **)&(thee->xf));
    Vmem_free(thee->vmem, 5*(thee->pmgp->ny), sizeof(double),
      (void **)&(thee->yf));
    Vmem_free(thee->vmem, 5*(thee->pmgp->nz), sizeof(double),
      (void **)&(thee->zf));
    Vmem_free(thee->vmem, 10*(thee->pmgp->ny)*(thee->pmgp->nz), sizeof(double),
      (void **)&(thee->gxcf));
    Vmem_free(thee->vmem, 10*(thee->pmgp->nx)*(thee->pmgp->nz), sizeof(double),
      (void **)&(thee->gycf));
    Vmem_free(thee->vmem, 10*(thee->pmgp->nx)*(thee->pmgp->ny), sizeof(double),
      (void **)&(thee->gzcf));
    Vmem_free(thee->vmem, (thee->pmgp->nx)*(thee->pmgp->ny)*(thee->pmgp->nz), 
      sizeof(int), (void **)&(thee->pvec));

    Vmem_dtor(&(thee->vmem));
}

/* ///////////////////////////////////////////////////////////////////////////
// Routine:  Vpmg_writeUHBD
//
// Purpose:  Write out a PMG array in UHBD grid format (ASCII)
//
// Args:     iodev        ==> output device type (file/buff/unix/inet)
//           iofmt        ==> output device format (ascii/xdr)
//           thost        ==> output hostname (for sockets)
//           fname        ==> output file/buff/unix/inet name
//           title => title to be inserted in grid
//           data => nx*ny*nz length array of data
//
// Notes:    The mesh spacing should be uniform
//
// Author:   Nathan Baker
/////////////////////////////////////////////////////////////////////////// */
VPUBLIC void Vpmg_writeUHBD(Vpmg *thee, const char *iodev, const char *iofmt, 
  const char *thost, const char *fname, char *title, double *data) {

    int icol, i, j, k, u;
    double xmin, ymin, zmin;
    Vio *sock;

    VASSERT(thee != VNULL);
    if ((thee->pmgp->hx!=thee->pmgp->hy) || (thee->pmgp->hy!=thee->pmgp->hzed) 
      || (thee->pmgp->hx!=thee->pmgp->hzed)) {
        Vnm_print(2, "Vpmg_writeUHBD: can't write UHBD mesh with non-uniform spacing\n");
        return;
    }

    /* Set up the virtual socket */
    sock = Vio_ctor(iodev,iofmt,thost,fname,"w");
    if (sock == VNULL) {
        Vnm_print(2, "Vpmg_writeUHBD: Problem opening virtual socket %s\n",
          fname);
        return;
    }
    if (Vio_connect(sock, 0) < 0) {
        Vnm_print(2, "Vpmg_writeUHBD: Problem connecting virtual socket %s\n",
          fname);
        return;
    }

    /* Write out the header */
    xmin = thee->pmgp->xcent - 0.5*(thee->pmgp->hx)*(thee->pmgp->nx-1);
    ymin = thee->pmgp->ycent - 0.5*(thee->pmgp->hy)*(thee->pmgp->ny-1);
    zmin = thee->pmgp->zcent - 0.5*(thee->pmgp->hzed)*(thee->pmgp->nz-1);
    Vio_printf(sock, "%72s\n", title);
    Vio_printf(sock, "%12.6E%12.6E%7d%7d%7d%7d%7d\n", 1.0, 0.0, -1, 0, 
      thee->pmgp->nz, 1, thee->pmgp->nz);
    Vio_printf(sock, "%7d%7d%7d%12.6E%12.6E%12.6E%12.6E\n", thee->pmgp->nx,
      thee->pmgp->ny, thee->pmgp->nz, thee->pmgp->hx, xmin, ymin, zmin);
    Vio_printf(sock, "%12.6E%12.6E%12.6E%12.6E\n", 0.0, 0.0, 0.0, 0.0);
    Vio_printf(sock, "%12.6E%12.6E%7d%7d", 0.0, 0.0, 0, 0);

    /* Write out the entries */
    icol = 0;
    for (k=0; k<thee->pmgp->nz; k++) {
        Vio_printf(sock, "\n%7d%7d%7d\n", k+1, thee->pmgp->nx, thee->pmgp->ny);
        icol = 0;
        for (j=0; j<thee->pmgp->ny; j++) {
            for (i=0; i<thee->pmgp->nx; i++) {
                u = k*(thee->pmgp->nx)*(thee->pmgp->ny)+j*(thee->pmgp->nx)+i;
                icol++;
                Vio_printf(sock, " %12.6E", data[u]);
                if (icol == 6) {
                    icol = 0;
                    Vio_printf(sock, "\n");
                }
            }
        }
    } 
    if (icol != 0) Vio_printf(sock, "\n");

    /* Close off the socket */
    Vio_connectFree(sock);
    Vio_dtor(&sock);
}

/* ///////////////////////////////////////////////////////////////////////////
// Routine:  Vpmg_readDX
//
// Purpose:  Read in a PMG array in OpenDX grid format 
//
// Args:     iodev      ==> output device type (file/buff/unix/inet)
//           iofmt      ==> output device format (ascii/xdr)
//           thost      ==> output hostname (for sockets)
//           fname      ==> output file/buff/unix/inet name
//           n{x,y,z}   ==> data array dimensions
//           h{x,y,z}   ==> mesh spacings
//           {x,y,z}min ==> lower grid corner
//           data       ==> nx*ny*nz length array of data (allocated in this
//                          routine)
//
// Notes:    All dimension information is given in order: z, y, x
//
// Author:   Nathan Baker
/////////////////////////////////////////////////////////////////////////// */
VPUBLIC void Vpmg_readDX(const char *iodev, const char *iofmt,
  const char *thost, const char *fname, 
  int *nx, int *ny, int *nz, 
  double *hx, double *hy, double *hzed, 
  double *xmin, double *ymin, double *zmin,
  double *data) {

    int i, j, k, itmp, u;
    double dtmp;
    char tok[VMAX_BUFSIZE];
    Vio *sock;

    /* Set up the virtual socket */
    sock = Vio_ctor(iodev,iofmt,thost,fname,"r");
    if (sock == VNULL) {
        Vnm_print(2, "Vpmg_readDX: Problem opening virtual socket %s\n",
          fname);
        return;
    }
    if (Vio_accept(sock, 0) < 0) {
        Vnm_print(2, "Vpmg_readDX: Problem accepting virtual socket %s\n",
          fname);
        return;
    }

    /* Read in the DX regular positions */
    /* Get "object" */
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "object"));
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    /* Get "1" */
    VJMPERR1(!strcmp(tok, "object"));
    /* Get "gridpositions" */
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "gridpositions"));
    /* Get "counts" */
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "counts"));
    /* Get nz */
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(1 == sscanf(tok, "%d", nz));
    /* Get ny */
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(1 == sscanf(tok, "%d", ny));
    /* Get nx */
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(1 == sscanf(tok, "%d", nx));
    /* Get "origin" */ 
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "origin"));
    /* Get zmin */
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(1 == sscanf(tok, "%lf", zmin));
    /* Get ymin */
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(1 == sscanf(tok, "%lf", ymin));
    /* Get xmin */
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(1 == sscanf(tok, "%lf", xmin));
    /* Get "delta" */ 
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "delta"));
    /* Get 0.0 */
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(1 == sscanf(tok, "%lf", &dtmp));
    VJMPERR1(dtmp == 0.0);
    /* Get 0.0 */
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(1 == sscanf(tok, "%lf", &dtmp));
    VJMPERR1(dtmp == 0.0);
    /* Get hz */
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(1 == sscanf(tok, "%lf", hzed));
    /* Get "delta" */ 
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "delta"));
    /* Get 0.0 */
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(1 == sscanf(tok, "%lf", &dtmp));
    VJMPERR1(dtmp == 0.0);
    /* Get hy */
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(1 == sscanf(tok, "%lf", hy));
    /* Get 0.0 */
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(1 == sscanf(tok, "%lf", &dtmp));
    VJMPERR1(dtmp == 0.0);
    /* Get "delta" */ 
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "delta"));
    /* Get hx */
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(1 == sscanf(tok, "%lf", hx));
    /* Get 0.0 */
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(1 == sscanf(tok, "%lf", &dtmp));
    VJMPERR1(dtmp == 0.0);
    /* Get 0.0 */
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(1 == sscanf(tok, "%lf", &dtmp));
    VJMPERR1(dtmp == 0.0);
    /* Get "object" */ 
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "object"));
    /* Get "2" */ 
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    /* Get "class" */ 
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "class"));
    /* Get "gridconnections" */ 
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "gridconnections"));
    /* Get "counts" */ 
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "counts"));
    /* Get the dimensions again */ 
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    /* Get "object" */ 
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "object"));
    /* Get # */ 
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    /* Get "class" */ 
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "class"));
    /* Get "array" */ 
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "array"));
    /* Get "type" */ 
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "type"));
    /* Get "double" */ 
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "double"));
    /* Get "rank" */ 
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "rank"));
    /* Get # */ 
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    /* Get "items" */ 
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "items"));
    /* Get # */ 
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(1 == sscanf(tok, "%d", &itmp));
    VJMPERR1(((*nx)*(*ny)*(*nz)) == itmp);
    /* Get "data" */ 
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "data"));
    /* Get "follows" */ 
    VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "follows"));

    /* Allocate space for the data */
    data = VNULL;
    data = Vmem_malloc(VNULL, (*nx)*(*ny)*(*nz), sizeof(double));
    if (data == VNULL) {
        Vnm_print(2, "Vpmg_readDX:  Unable to allocate space for data!\n");
        return;
    }

    for (k=0; k<*nz; k++) {
        for (j=0; j<*ny; j++) {
            for (i=0; i<*nx; i++) {
                u = k*(*nx)*(*ny)+j*(*nx)+i;
                VJMPERR2(1 == Vio_scanf(sock, "%s", tok));
                VJMPERR1(1 == sscanf(tok, "%lf", &dtmp));
                data[u] = dtmp;
            }
        }
    }

    /* Close off the socket */
    Vio_acceptFree(sock);
    Vio_dtor(&sock);

    return;

  VERROR1:
    Vio_dtor(&sock);
    Vnm_print(2, "Vpmg_readDX:  Format problem with input file <%s>\n", 
      fname);
    return;

  VERROR2:
    Vio_dtor(&sock);
    Vnm_print(2, "Vpmg_readDX:  I/O problem with input file <%s>\n", 
      fname);
    return;
   


}



/* ///////////////////////////////////////////////////////////////////////////
// Routine:  Vpmg_writeDX
//
// Purpose:  Write out a PMG array in OpenDX grid format (ASCII)
//
// Args:     iodev        ==> output device type (file/buff/unix/inet)
//           iofmt        ==> output device format (ascii/xdr)
//           thost        ==> output hostname (for sockets)
//           fname        ==> output file/buff/unix/inet name
//           title => title to be inserted in grid
//           data => nx*ny*nz length array of data
//
// Notes:    All dimension information is given in order: z, y, x
//
// Author:   Nathan Baker
/////////////////////////////////////////////////////////////////////////// */
VPUBLIC void Vpmg_writeDX(Vpmg *thee, const char *iodev, const char *iofmt,
  const char *thost, const char *fname, char *title, double *data) {

    int icol, i, j, k, u;
    double xmin, ymin, zmin;
    Vio *sock;

    /* Set up the virtual socket */
    sock = Vio_ctor(iodev,iofmt,thost,fname,"w");
    if (sock == VNULL) {
        Vnm_print(2, "Vpmg_writeDX: Problem opening virtual socket %s\n",
          fname);
        return;
    }
    if (Vio_connect(sock, 0) < 0) {
        Vnm_print(2, "Vpmg_writeDX: Problem connecting virtual socket %s\n",
          fname);
        return;
    }

    /* Write off the title */
    Vio_printf(sock, "# Electrostatic potential data from APBS/PMG\n");
    Vio_printf(sock, "# \n");
    Vio_printf(sock, "# %s\n", title);
    Vio_printf(sock, "# \n");

    /* Write off the DX regular positions */
    Vio_printf(sock, "object 1 class gridpositions counts %d %d %d\n",
      thee->pmgp->nz, thee->pmgp->ny, thee->pmgp->nx);
    xmin = thee->pmgp->xcent - 0.5*(thee->pmgp->hx)*(thee->pmgp->nx-1);
    ymin = thee->pmgp->ycent - 0.5*(thee->pmgp->hy)*(thee->pmgp->ny-1);
    zmin = thee->pmgp->zcent - 0.5*(thee->pmgp->hzed)*(thee->pmgp->nz-1);
    Vio_printf(sock, "origin %12.6E %12.6E %12.6E\n", zmin, ymin, xmin);
    Vio_printf(sock, "delta %12.6E %12.6E %12.6E\n", 0.0, 0.0, thee->pmgp->hzed);
    Vio_printf(sock, "delta %12.6E %12.6E %12.6E\n", 0.0, thee->pmgp->hy, 0.0);
    Vio_printf(sock, "delta %12.6E %12.6E %12.6E\n", thee->pmgp->hx, 0.0, 0.0);

    /* Write off the DX regular connections */
    Vio_printf(sock, "object 2 class gridconnections counts %d %d %d\n",
      thee->pmgp->nz, thee->pmgp->ny, thee->pmgp->nx);

    /* Write off the DX data */
    Vio_printf(sock, "object 3 class array type double rank 0 items %d data follows\n",
      (thee->pmgp->nx*thee->pmgp->ny*thee->pmgp->nz));
    icol = 0;
    for (k=0; k<thee->pmgp->nz; k++) {
        for (j=0; j<thee->pmgp->ny; j++) {
            for (i=0; i<thee->pmgp->nx; i++) {
                u = k*(thee->pmgp->nx)*(thee->pmgp->ny)+j*(thee->pmgp->nx)+i;
                Vio_printf(sock, "%12.6E ", data[u]);
                icol++;
                if (icol == 3) {
                    icol = 0;
                    Vio_printf(sock, "\n");
                }
            }
        }
    }
    if (icol != 0) Vio_printf(sock, "\n");
                
    /* Create the field */
    Vio_printf(sock, "attribute \"dep\" string \"positions\"\n");
    Vio_printf(sock, "object \"regular positions regular connections\" class field\n");
    Vio_printf(sock, "component \"positions\" value 1\n");
    Vio_printf(sock, "component \"connections\" value 2\n");
    Vio_printf(sock, "component \"data\" value 3\n");

    /* Close off the socket */
    Vio_connectFree(sock);
    Vio_dtor(&sock);

}

/* ///////////////////////////////////////////////////////////////////////////
// Routine:  Vpmg_setPart
//
// Purpose:  Set partition information which restricts the calculation of
//           observables to a (rectangular) subset of the problem domain
//
// Args:     [xyz]min => lower corner
//           [xyz]max => upper corner
//
// Author:   Nathan Baker
/////////////////////////////////////////////////////////////////////////// */
VPUBLIC void Vpmg_setPart(Vpmg *thee, double xmin, double ymin, double zmin,
           double xmax, double ymax, double zmax) {

    int i, j, k, nx, ny, nz;

    nx = thee->pmgp->nx;
    ny = thee->pmgp->ny;
    nz = thee->pmgp->nz;

    /* We need have called Vpmg_fillco first */
    VASSERT(thee->filled == 1);

    /* Load up pvec */
    for (i=0; i<(nx*ny*nz); i++) thee->pvec[i] = 0;
    for (i=0; i<nx; i++) {
        if ( (thee->xf[i]<=xmax) && 
             (thee->xf[i]>=xmin)) {
            for (j=0; j<thee->pmgp->ny; j++) {
                if ( (thee->yf[j]<=ymax) && 
                     (thee->yf[j]>=ymin)) {
                    for (k=0; k<thee->pmgp->nz; k++) {
                        if ( (thee->zf[k]<=zmax) && 
                             (thee->zf[k]>=zmin)) thee->pvec[IJK(i,j,k)] = 1;
                    }
                }
            }
        }
    }

}

/* ///////////////////////////////////////////////////////////////////////////
// Routine:  Vpmg_unsetPart
//
// Purpose:  Remove partition information
//
// Author:   Nathan Baker
/////////////////////////////////////////////////////////////////////////// */
VPUBLIC void Vpmg_unsetPart(Vpmg *thee) {

    int i, nx, ny, nz;

    VASSERT(thee != VNULL);

    nx = thee->pmgp->nx;
    ny = thee->pmgp->ny;
    nz = thee->pmgp->nz;

    for (i=0; i<(nx*ny*nz); i++) thee->pvec[i] = 1;
}

/* ///////////////////////////////////////////////////////////////////////////
// Routine:  Vpmg_readArrayDX
//
// Purpose:  Read and allocate an array from a DX file
//
// Args:     iodev    ==> output device type (file/buff/unix/inet)
//           iofmt    ==> output device format (ascii/xdr)
//           thost    ==> output hostname (for sockets)
//           fname    ==> output file/buff/unix/inet name
//           n[xyz]   ==> mesh dimensions
//           h[xyz]   ==> mesh spacings
//           [xyz]low ==> mesh lower corner
//           data     ==> A pointer to a pointer which will become an array of
//                        doubles containing the data (allocated in this
//                        function)
//
// Notes:    The array "data" is allocated by this function!
//
// Author:   Nathan Baker
/////////////////////////////////////////////////////////////////////////// */
VPUBLIC int Vpmg_readArrayDX(const char *iodev, const char *iofmt,
  const char *thost, const char *fname, double *xlow, double *ylow, 
  double *zlow, double *hx, double *hy, double *hzed, int *nx, int *ny, 
  int *nz, double **data) {

    int u, inum;
    double dnum;
    char tok[VMAX_BUFSIZE];
    Vio *sock;
  
    int iodebug = 0;

    /* Set up the virtual socket */
    sock = Vio_ctor(iodev,iofmt,thost,fname,"r");
    if (sock == VNULL) {
        Vnm_print(2, "Vpmg_readArrayDX: Problem opening virtual socket %s\n",
          fname);
        return 0;
    }
    if (Vio_accept(sock, 0) < 0) {
        Vnm_print(2, "Vpmg_readArrayDX: Problem connecting virtual socket %s\n",
          fname);
        return 0;
    }
    Vio_setCommChars(sock, "#");

    /* Grab the "object" line which contains the mesh dimensions */
    VJMPERR1(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "object")); 
    VJMPERR1(1 == Vio_scanf(sock, "%d", &inum));
    VJMPERR1(inum == 1);
    VJMPERR1(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "class")); 
    VJMPERR1(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "gridpositions")); 
    VJMPERR1(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "counts")); 
    VJMPERR1(1 == Vio_scanf(sock, "%d", &inum));
    *nz = inum;
    VJMPERR1(1 == Vio_scanf(sock, "%d", &inum));
    *ny = inum;
    VJMPERR1(1 == Vio_scanf(sock, "%d", &inum));
    *nx = inum;

    Vnm_print(iodebug, "Vpmg_readArrayDX: Mesh dimensions = %d x %d x %d.\n",
      *nx, *ny, *nz);

    /* Grab the "origin" line which contains the lower corner coords */
    VJMPERR1(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "origin")); 
    VJMPERR1(1 == Vio_scanf(sock, "%le", &dnum));
    *zlow = dnum;
    VJMPERR1(1 == Vio_scanf(sock, "%le", &dnum));
    *ylow = dnum;
    VJMPERR1(1 == Vio_scanf(sock, "%le", &dnum));
    *xlow = dnum;

    Vnm_print(iodebug, "Vpmg_readArrayDX: Mesh origin = (%g, %g, %g).\n",
      *xlow, *ylow, *zlow);
    
    /* Grab the "z" direction mesh spacing */
    VJMPERR1(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "delta"));
    VJMPERR1(1 == Vio_scanf(sock, "%le", &dnum));
    VJMPERR1(1 == Vio_scanf(sock, "%le", &dnum));
    VJMPERR1(1 == Vio_scanf(sock, "%le", &dnum));
    *hzed = dnum;

    /* Grab the "y" direction mesh spacing */
    VJMPERR1(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "delta"));
    VJMPERR1(1 == Vio_scanf(sock, "%le", &dnum));
    VJMPERR1(1 == Vio_scanf(sock, "%le", &dnum));
    *hy = dnum;
    VJMPERR1(1 == Vio_scanf(sock, "%le", &dnum));

    /* Grab the "x" direction mesh spacing */
    VJMPERR1(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "delta"));
    VJMPERR1(1 == Vio_scanf(sock, "%le", &dnum));
    *hx = dnum;
    VJMPERR1(1 == Vio_scanf(sock, "%le", &dnum));
    VJMPERR1(1 == Vio_scanf(sock, "%le", &dnum));

    Vnm_print(iodebug, "Vpmg_readArrayDX: Mesh spacing = (%g, %g, %g).\n",
      *hx, *hy, *hzed);

    /* Grab a line we don't care about */
    VJMPERR1(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "object"));
    VJMPERR1(1 == Vio_scanf(sock, "%d", &inum));
    VJMPERR1(2 == inum);
    VJMPERR1(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "class"));
    VJMPERR1(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "gridconnections"));
    VJMPERR1(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "counts"));
    VJMPERR1(1 == Vio_scanf(sock, "%d", &inum));
    VJMPERR1(*nz == inum);
    VJMPERR1(1 == Vio_scanf(sock, "%d", &inum));
    VJMPERR1(*ny == inum);
    VJMPERR1(1 == Vio_scanf(sock, "%d", &inum));
    VJMPERR1(*nx == inum);

    /* Grab another line we don't care about */
    VJMPERR1(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "object"));
    VJMPERR1(1 == Vio_scanf(sock, "%d", &inum));
    VJMPERR1(3 == inum);
    VJMPERR1(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "class"));
    VJMPERR1(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "array"));
    VJMPERR1(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "type"));
    VJMPERR1(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "double"));
    VJMPERR1(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "rank"));
    VJMPERR1(1 == Vio_scanf(sock, "%d", &inum));
    VJMPERR1(0 == inum);
    VJMPERR1(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "items"));
    VJMPERR1(1 == Vio_scanf(sock, "%d", &inum));
    VJMPERR1((*nx)*(*ny)*(*nz) == inum);
    VJMPERR1(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "data"));
    VJMPERR1(1 == Vio_scanf(sock, "%s", tok));
    VJMPERR1(!strcmp(tok, "follows"));
    
    /* Allocate space for the data */
    *data = (double *)Vmem_malloc(VNULL, (*nx)*(*ny)*(*nz), sizeof(double));
    if (*data == VNULL) {
        Vnm_print(2, "Vpmg_readArrayDX:  Failed to allocate array space!\n");
        return 0;
    } 

    /* Read in the data */
    u = 0;
    while (1) {
        VJMPERR1(1 == Vio_scanf(sock, "%le", &dnum));
        (*data)[u] = dnum;
        u++;
        if (u == (*nx)*(*ny)*(*nz)) break;
    }
 
    /* Close off the socket */
    Vio_connectFree(sock);
    Vio_dtor(&sock);

    return 1;

  VERROR1:
    Vio_dtor(&sock);
    Vnm_print(2, "Vpmg_readArrayDX: Format problem with input file %s\n", fname);
    return 0;


}

/* ///////////////////////////////////////////////////////////////////////////
// Routine:  Vpmg_fillAcc
//
// Purpose:  Fill the specified array with accessibility values
//
// Args:     vec   The vector to be filled (must be nx*ny*nz in length)
//           meth  The accessibility definition to use:
//                  0 => Mol surf (uses parm)
//                  1 => VdW surf
//                  2 => Inflated VdW surf (uses parm)
//           parm  Parameter for surface definition
//
// Author:   Nathan Baker
/////////////////////////////////////////////////////////////////////////// */
VPUBLIC void Vpmg_fillAcc(Vpmg *thee, double *vec, int meth, double parm) {

    Vacc *acc = VNULL;
    Vpbe *pbe = VNULL;
    double position[3];
    int i, j, k, nx, ny, nz;

    pbe = thee->pbe;
    acc = Vpbe_getVacc(pbe);
    nx = thee->pmgp->nx;
    ny = thee->pmgp->ny;
    nz = thee->pmgp->nz;

    if (meth == 0) {
        Vnm_print(0, "Vpmg_fillAcc: using molecular surface with %g A probe\n",
          parm);
    } else if (meth == 1) {
        Vnm_print(0, "Vpmg_fillAcc: using van der Waals surface\n");
    } else if (meth == 2) {
        Vnm_print(0, "Vpmg_fillAcc: using inflated van der Waals surface with %g A probe\n",
          parm);
    } else {
        Vnm_print(2, "Vpmg_fillAcc: invalid surface method (%d)!\n", meth);
        VASSERT(0);
    }


    for (k=0; k<nz; k++) {
        for (j=0; j<ny; j++) {
            for (i=0; i<nx; i++) {

                position[0] = thee->xf[i];
                position[1] = thee->yf[j];
                position[2] = thee->zf[k];

                /* the scalar (0th derivative) entry */
                if (meth == 0) {
                    vec[IJK(i,j,k)] = (double)(Vacc_molAcc(acc,position,parm));
                } else if (meth == 1) {
                    vec[IJK(i,j,k)] = (double)(Vacc_vdwAcc(acc,position));
                } else if (meth == 2) {
                    vec[IJK(i,j,k)] = (double)(Vacc_ivdwAcc(acc,position,parm));
                }
            }
        }
    }
}

#undef VPMGSMALL
