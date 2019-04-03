/** @file
Intel-only SMM Child Dispatcher Protocol.

This protocol provides a parent dispatch service for a collection of
chipset-specific SMI source.

Copyright (c) 2013-2015 Intel Corporation.

SPDX-License-Identifier: BSD-2-Clause-Patent

**/


#ifndef __SMM_ICHN_DISPATCH2_H__
#define __SMM_ICHN_DISPATCH2_H__

//
// Share some common definitions with Framework SMM
//
#include <Protocol/SmmIchnDispatch.h>

#include <PiSmm.h>

//
// Global ID for the ICH SMI Protocol
//
#define EFI_SMM_ICHN_DISPATCH2_PROTOCOL_GUID \
  { \
    0xadf3a128, 0x416d, 0x4060, {0x8d, 0xdf, 0x30, 0xa1, 0xd7, 0xaa, 0xb6, 0x99 } \
  }

typedef struct _EFI_SMM_ICHN_DISPATCH2_PROTOCOL EFI_SMM_ICHN_DISPATCH2_PROTOCOL;

typedef struct {
  EFI_SMM_ICHN_SMI_TYPE Type;
} EFI_SMM_ICHN_REGISTER_CONTEXT;

//
// Member functions
//
/**
  Register a child SMI source dispatch function with a parent SMM driver

  @param  This                  Protocol instance pointer.
  @param  DispatchFunction      Pointer to dispatch function to be invoked for
                                this SMI source
  @param  RegisterContext       Pointer to the dispatch function's context.
                                The caller fills this context in before calling
                                the register function to indicate to the register
                                function the ICHN SMI source for which the dispatch
                                function should be invoked.
  @param  DispatchHandle        Handle generated by the dispatcher to track the
                                function instance.

  @retval EFI_SUCCESS           The dispatch function has been successfully
                                registered and the SMI source has been enabled.
  @retval EFI_DEVICE_ERROR      The driver was unable to enable the SMI source.
  @retval EFI_OUT_OF_RESOURCES  Not enough memory (system or SMM) to manage this
                                child.
  @retval EFI_INVALID_PARAMETER RegisterContext is invalid. The ICHN input value
                                is not within valid range.

**/
typedef
EFI_STATUS
(EFIAPI *EFI_SMM_ICHN_DISPATCH2_REGISTER) (
  IN CONST EFI_SMM_ICHN_DISPATCH2_PROTOCOL   *This,
  IN       EFI_SMM_HANDLER_ENTRY_POINT2      DispatchFunction,
  IN OUT   EFI_SMM_ICHN_REGISTER_CONTEXT     *RegisterContext,
     OUT   EFI_HANDLE                        *DispatchHandle
  );

/**
  Unregister a child SMI source dispatch function with a parent SMM driver

  @param  This                  Protocol instance pointer.
  @param  DispatchHandle        Handle of dispatch function to deregister.

  @retval EFI_SUCCESS           The dispatch function has been successfully
                                unregistered and the SMI source has been disabled
                                if there are no other registered child dispatch
                                functions for this SMI source.
  @retval EFI_INVALID_PARAMETER Handle is invalid.
  @retval other

**/
typedef
EFI_STATUS
(EFIAPI *EFI_SMM_ICHN_DISPATCH2_UNREGISTER) (
  IN EFI_SMM_ICHN_DISPATCH2_PROTOCOL          *This,
  IN EFI_HANDLE                               DispatchHandle
  );

//
// Interface structure for the SMM Ich n specific SMI Dispatch Protocol
//
/**
  @par Protocol Description:
  Provides a parent dispatch service for ICH SMI sources.

  @param Register
  Installs a child service to be dispatched by this protocol.

  @param UnRegister
  Removes a child service dispatched by this protocol.

**/
struct _EFI_SMM_ICHN_DISPATCH2_PROTOCOL {
  EFI_SMM_ICHN_DISPATCH2_REGISTER   Register;
  EFI_SMM_ICHN_DISPATCH2_UNREGISTER UnRegister;
};

extern EFI_GUID gEfiSmmIchnDispatch2ProtocolGuid;

#endif
