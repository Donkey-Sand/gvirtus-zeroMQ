/*
 * gVirtuS -- A GPGPU transparent virtualization component.
 *
 * Copyright (C) 2009-2010  The University of Napoli Parthenope at Naples.
 *
 * This file is part of gVirtuS.
 *
 * gVirtuS is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * gVirtuS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with gVirtuS; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * Written by: Giuseppe Coviello <giuseppe.coviello@uniparthenope.it>,
 *             Department of Applied Science
 */

#include "CudaRt.h"

using namespace std;

extern "C" __host__ cudaError_t CUDARTAPI cudaDriverGetVersion(int *driverVersion) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddHostPointerForArguments(driverVersion);
    CudaRtFrontend::Execute("cudaDriverGetVersion");
    if(CudaRtFrontend::Success())
        *driverVersion = *(CudaRtFrontend::GetOutputHostPointer<int>());
    return CudaRtFrontend::GetExitCode();
}

extern "C" __host__ cudaError_t CUDARTAPI cudaRuntimeGetVersion(int *runtimeVersion) {
    CudaRtFrontend::Prepare();
    CudaRtFrontend::AddHostPointerForArguments(runtimeVersion);
    CudaRtFrontend::Execute("cudaDriverGetVersion");
    if(CudaRtFrontend::Success())
        *runtimeVersion = *(CudaRtFrontend::GetOutputHostPointer<int>());
    return CudaRtFrontend::GetExitCode();
}
