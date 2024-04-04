/** @file

  Copyright (c) 2006 - 2015, Intel Corporation. All rights reserved.<BR>
  SPDX-License-Identifier: BSD-2-Clause-Patent

**/

#include <Uefi.h>

#include <Library/BaseLib.h>
#include <Library/DebugLib.h>
#include <Library/QemuLoadImageLib.h>
#include <Library/ReportStatusCodeLib.h>
#include <Library/UefiLib.h>

#include <Library/TimerLib.h>
#include <inttypes.h>

static inline UINT64 _rdtsc() {
   UINT32 hi, lo;
   __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
   return ((UINT64)(lo)|((UINT64)(hi)<<32));
}

EFI_STATUS
TryRunningQemuKernel (
  VOID
  )
{
  EFI_STATUS  Status;
  EFI_HANDLE  KernelImageHandle;

  UINT64 StartTicks = _rdtsc();
  DEBUG ((
    DEBUG_INFO,
    "%a: CSG-M4G1C: BEGIN (ticks): %" PRIu64 "\n",
    __FUNCTION__,
    StartTicks
  ));

  Status = QemuLoadKernelImage (&KernelImageHandle);
  if (EFI_ERROR (Status)) {
    return Status;
  }

  //
  // Signal the EVT_SIGNAL_READY_TO_BOOT event
  //
  EfiSignalEventReadyToBoot ();

  REPORT_STATUS_CODE (
    EFI_PROGRESS_CODE,
    (EFI_SOFTWARE_DXE_BS_DRIVER | EFI_SW_DXE_BS_PC_READY_TO_BOOT_EVENT)
    );

  UINT64 EndTicks = _rdtsc();
  DEBUG ((
    DEBUG_INFO,
    "%a: CSG-M4G1C: END (ticks): %" PRIu64 "\n",
    __FUNCTION__,
    EndTicks
  ));
  UINT64 Frequency = GetPerformanceCounterProperties (NULL, NULL);
  DEBUG ((
    DEBUG_INFO,
    "%a: CSG-M4G1C: 3ND (ticks): %" PRIu64 " Freq: %" PRIu64 "\n",
    __FUNCTION__,
    EndTicks,
    Frequency
  ));

  //
  // Start the image.
  //
  Status = QemuStartKernelImage (&KernelImageHandle);
  if (EFI_ERROR (Status)) {
    DEBUG ((
      DEBUG_ERROR,
      "%a: QemuStartKernelImage(): %r\n",
      __func__,
      Status
      ));
  }

  //
  // CSG: CoCo boots directly from the initrd, so we never return from the StartKernel call
  //
  DEBUG ((
    DEBUG_INFO,
    "%a: CSG-M4G1C: NOT HERE\n",
    __FUNCTION__
  ));

  QemuUnloadKernelImage (KernelImageHandle);

  return Status;
}
