
/******************************************************************************
 * 
 * Name: namespace.h - Namespace subcomponent prototypes and defines
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999, Intel Corp.  All rights 
 * reserved.
 *
 * 2. License
 * 
 * 2.1. Intel grants, free of charge, to any person ("Licensee") obtaining a 
 * copy of the source code appearing in this file ("Covered Code") a license 
 * under Intel's copyrights in the base code distributed originally by Intel 
 * ("Original Intel Code") to copy, make derivatives, distribute, use and 
 * display any portion of the Covered Code in any form; and
 *
 * 2.2. Intel grants Licensee a non-exclusive and non-transferable patent 
 * license (without the right to sublicense), under only those claims of Intel
 * patents that are infringed by the Original Intel Code, to make, use, sell, 
 * offer to sell, and import the Covered Code and derivative works thereof 
 * solely to the minimum extent necessary to exercise the above copyright 
 * license, and in no event shall the patent license extend to any additions to
 * or modifications of the Original Intel Code.  No other license or right is 
 * granted directly or by implication, estoppel or otherwise;
 *
 * the above copyright and patent license is granted only if the following 
 * conditions are met:
 *
 * 3. Conditions 
 *
 * 3.1. Redistribution of source code of any substantial portion of the Covered 
 * Code or modification must include the above Copyright Notice, the above 
 * License, this list of Conditions, and the following Disclaimer and Export 
 * Compliance provision.  In addition, Licensee must cause all Covered Code to 
 * which Licensee contributes to contain a file documenting the changes 
 * Licensee made to create that Covered Code and the date of any change.  
 * Licensee must include in that file the documentation of any changes made by
 * any predecessor Licensee.  Licensee must include a prominent statement that
 * the modification is derived, directly or indirectly, from Original Intel 
 * Code.
 *
 * 3.2. Redistribution in binary form of any substantial portion of the Covered 
 * Code or modification must reproduce the above Copyright Notice, and the 
 * following Disclaimer and Export Compliance provision in the documentation 
 * and/or other materials provided with the distribution.
 *
 * 3.3. Intel retains all right, title, and interest in and to the Original 
 * Intel Code.
 *
 * 3.4. Neither the name Intel nor any other trademark owned or controlled by 
 * Intel shall be used in advertising or otherwise to promote the sale, use or 
 * other dealings in products derived from or relating to the Covered Code 
 * without prior written authorization from Intel.
 *
 * 4. Disclaimer and Export Compliance
 *
 * 4.1. INTEL MAKES NO WARRANTY OF ANY KIND REGARDING ANY SOFTWARE PROVIDED 
 * HERE.  ANY SOFTWARE ORIGINATING FROM INTEL OR DERIVED FROM INTEL SOFTWARE 
 * IS PROVIDED "AS IS," AND INTEL WILL NOT PROVIDE ANY SUPPORT,  ASSISTANCE, 
 * INSTALLATION, TRAINING OR OTHER SERVICES.  INTEL WILL NOT PROVIDE ANY 
 * UPDATES, ENHANCEMENTS OR EXTENSIONS.  INTEL SPECIFICALLY DISCLAIMS ANY 
 * IMPLIED WARRANTIES OF MERCHANTABILITY, NONINFRINGEMENT AND FITNESS FOR A 
 * PARTICULAR PURPOSE. 
 *
 * 4.2. IN NO EVENT SHALL INTEL HAVE ANY LIABILITY TO LICENSEE, ITS LICENSEES 
 * OR ANY OTHER THIRD PARTY, FOR ANY LOST PROFITS, LOST DATA, LOSS OF USE OR 
 * COSTS OF PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, OR FOR ANY INDIRECT, 
 * SPECIAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THIS AGREEMENT, UNDER ANY 
 * CAUSE OF ACTION OR THEORY OF LIABILITY, AND IRRESPECTIVE OF WHETHER INTEL 
 * HAS ADVANCE NOTICE OF THE POSSIBILITY OF SUCH DAMAGES.  THESE LIMITATIONS 
 * SHALL APPLY NOTWITHSTANDING THE FAILURE OF THE ESSENTIAL PURPOSE OF ANY 
 * LIMITED REMEDY.
 *
 * 4.3. Licensee shall not export, either directly or indirectly, any of this 
 * software or system incorporating such software without first obtaining any 
 * required license or other approval from the U. S. Department of Commerce or 
 * any other agency or department of the United States Government.  In the 
 * event Licensee exports any such software from the United States or re-
 * exports any such software from a foreign destination, Licensee shall ensure
 * that the distribution and export/re-export of the software is in compliance 
 * with all laws, regulations, orders, or other restrictions of the U.S. Export 
 * Administration Regulations. Licensee agrees that neither it nor any of its 
 * subsidiaries will export/re-export any technical data, process, software, or 
 * service, directly or indirectly, to any country for which the United States 
 * government or any agency thereof requires an export license, other 
 * governmental approval, or letter of assurance, without first obtaining such
 * license, approval or letter.
 *
 *****************************************************************************/


#ifndef __NAMESPACE_H__
#define __NAMESPACE_H__

#include <datatypes.h>
#include <acpitables.h>
#include <acpiobj.h>
#include <pnp.h>


#define ACPILIB_DATA_FILE_VERSION "ADF-001"


/* 
 * If USE_HASHING is not set, there will be an (nte *) prefix to each name
 * table, containing either a NULL pointer or the address of the next array
 * of nte's in the scope.
 */

#ifndef USE_HASHING
#define NEXTSEG(NameTbl) ((nte **)NameTbl)[-1]
#endif

/* Names are 4 bytes long */

#define ACPI_NAME_SIZE          4

/* 
 * An NsHandle (which is actually an nte *) can appear in some contexts,
 * such as on apObjStack, where a pointer to an OBJECT_DESCRIPTOR can also
 * appear.  This macro is used to distinguish them.
 *
 * The first byte of an nte is a character of the name segment, which will
 * be accepted by NcOK().  The first byte of an OBJECT_DESCRIPTOR is the
 * ValTyp field, whose (UINT8) value comes from the NsType enumeration.
 * Valid NsType values must not include any character acceptable in a name.
 */

#define IsNsHandle(h)           (NcOK ((INT32) * (char *) (h)))


/* To search the entire name space, pass this as SearchBase */

#define  NS_ALL                 ((NsHandle)0)


#define NUM_NS_TYPES            37


/* 
 * Elements of NsProperties are bit significant
 * and should be one-to-one with values of NsType in acpinmsp.h
 */
#define NEWSCOPE                1   /* a definition of this type opens a name scope */
#define LOCAL                   2   /* suppress search of enclosing scopes */


/* UINT32 definitions of the predefined namespace names */

#define NS_ROOT                 '/   '
#define NS_SYSTEM_BUS           '_BS_'



/* 
 * Names built-in to the interpreter
 *
 * Initial values are currently supported only for types String and Number.
 * To avoid type punning, both are specified as strings in this table.
 */

static struct InitVal {
    char        *Name;
    NsType      Type;
    char        *Val;
} PreDefinedNames[] = {
    {"_GPE",    TYPE_DefAny},
    {"_PR_",    TYPE_DefAny},
    {"_SB_",    TYPE_DefAny},
    {"_SI_",    TYPE_DefAny},
    {"_TZ_",    TYPE_DefAny},
    {"_REV",    TYPE_Number, "2"},
    {"_OS_",    TYPE_String, "Intel AML interpreter"},
    {"_GL_",    TYPE_Mutex},

    /* Table terminator */

    {(char *)0, TYPE_Any}
};


/* Namespace globals */

extern SCOPE_STACK              ScopeStack[];
extern SCOPE_STACK              *CurrentScope;
extern char                     BadType[];
extern char                     *NsTypeNames[NUM_NS_TYPES];
extern INT32                    NsProperties[NUM_NS_TYPES];



/* External interfaces?? TBD - these shouldn't be here */

INT32
AcpiLoadNameSpace  (
    INT32               DisplayAmlDuringLoad);

void
AcpiLocalCleanup (
    void);

void 
InitAcpiLibGlobals (
    void);

INT32
LoadNameSpace (
    INT32               DisplayAmlDuringLoad);

INT32
AcpiSetFirmwareWakingVector (
    UINT32              PhysicalAddress);

INT32
AcpiGetFirmwareWakingVector (
    UINT32              *PhysicalAddress);


/*
 * ACPI Table functions - nstables
 */

INT32
NsFindRootSystemDescriptorPointer (
    ROOT_SYSTEM_DESCRIPTOR_POINTER  ** RSDP,
    OSD_FILE                        *InputFile);

INT32
NsVerifyTableChecksum (
    void                *TableHeader, 
    INT32               DisplayBitFlags);

void * 
NsGetTable (
    UINT32              PhysicalAddress, 
    OSD_FILE            *InputFile);

void * 
NsGetFACS (
    OSD_FILE            *InputFile);


/*
 * Top-level namespace access - nsaccess
 */


INT32
PriUnloadNameSpace (
    void);

void
NsSetup (
    void);

NsHandle
NsEnter (
    char                *Name, 
    NsType              Type, 
    OpMode              iLE);


/*
 * Scope manipulation - nsscope
 */

INT32
NsOpensScope (
    NsType              Type);

nte *
NsSearchTable (
    char                *NamSeg, 
    nte                 *NameTbl, 
    INT32               TableSize, 
    OpMode              LoadMode, 
    NsType              Type);

char *
NsNameOfScope (
    nte                 *EntryToSearch);

char *
NsNameOfCurrentScope (
    void);

char *
NsFullyQualifiedName (
    NsHandle            Look);

void
NsSetMethod (
    NsHandle            ObjHandle, 
    ptrdiff_t           Offset, 
    INT32               Length);

void
NsSetValue (
    NsHandle            ObjHandle, 
    ACPI_OBJECT_HANDLE  v, 
    UINT8               ValTyp);

BOOLEAN
NsPatternMatch (
    nte                 *ObjEntry, 
    char                *SearchFor);
        
void *
NsNameCompare (
    NsHandle            ObjHandle, 
    INT32               Level, 
    void                *Context);

void
NsLowFindNames (
    nte                 *ThisEntry, 
    char                *SearchFor,
    INT32               *Count, 
    NsHandle            List[], 
    INT32               MaxDepth);

NsHandle *
NsFindNames (
    char                *SearchFor, 
    NsHandle            SearchBase, 
    INT32               MaxDepth);

NsHandle
NsGetHandle (
    char                *Name, 
    NsHandle            Scope);

void *
NsCompareValue (
    NsHandle            ObjHandle, 
    INT32               Level, 
    void                *ObjDesc);

NsHandle
NsFindValue (
    OBJECT_DESCRIPTOR   *ObjDesc, 
    NsHandle            SearchBase, 
    INT32               MaxDepth);


/*
 * Scope Stack manipulation - nsstack
 */

void
NsPushCurrentScope (
    nte                 *NewScope, 
    NsType              Type);

void
NsPushMethodScope (
    NsHandle            nNewScope);

INT32
NsPopCurrent (
    NsType              Type);


/*
 * Parent/Child/Peer utility functions - nsfamily
 */

char *
NsFindParentName (
    nte                 *EntryToSearch, 
    INT32               Trace);

INT32
NsExistDownstreamSibling (
    nte                 *ThisEntry, 
    INT32               Size, 
    nte                 *Appendage);

NsHandle 
NsGetParentHandle (
    NsHandle            Look);


/* 
 * Namespace dump/print utilities - nsdump
 */

void
NsDumpTables (
    NsHandle            SearchBase, 
    INT32               MaxDepth);

void
NsDumpEntry (
    NsHandle            Handle);


/*
 * Utility functions - nsutils
 */

nte *
NsAllocateNteDesc (
    INT32               Size);

UINT8
NsChecksum (
    void                *Buffer,
    UINT32              Length);

void *
NsWalkNamespace (
    NsType              Type, 
    NsHandle            StartHandle, 
    UINT32              MaxDepth,
    void                * (* UserFunction)(NsHandle, UINT32, void *), 
    void                *Context);

NsType
NsGetType (
    NsHandle            ObjHandle);

void *
NsGetValue (
    NsHandle            ObjHandle);

INT32
NsLocal (
    NsType              Type);

char *
NsInternalizeName (
    char                *DottedName);

INT32
IsNsValue (
    OBJECT_DESCRIPTOR   *pOD);

INT32
NsMarkNS(
    void);



/*
 * TBD: What is PLUMBER??
 */

#ifndef PLUMBER

/* dummy macros to make calls go away */

#define MarkStaticBlocks(Count)
#define RegisterStaticBlockPtr(BP)

#else

void
RegisterStaticBlockPtr (
    void                **BP);

void
MarkStaticBlocks (
    INT32               *Count);

#endif /* PLUMBER */




#endif /* __NAMESPACE_H__ */
