# Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
# SPDX-License-Identifier: Apache-2.0

HARNESS_ENTRY = harness
HARNESS_FILE = xFindObjectWithLabelAndClass_harness

# This should be a unique identifier for this proof, and will appear on the
# Litani dashboard. It can be human-readable and contain spaces if you wish.
PROOF_UID = xFindObjectWithLabelAndClass

DEFINES +=
INCLUDES +=

REMOVE_FUNCTION_BODY +=
UNWINDSET += strlen.0:32

PROOF_SOURCES += $(PROOFDIR)/$(HARNESS_FILE).c
PROOF_SOURCES += $(SRCDIR)/test/cbmc/stubs/pkcs11_interface_stubs.c
PROJECT_SOURCES += $(SRCDIR)/source/core_pkcs11.c

include ../Makefile.common
