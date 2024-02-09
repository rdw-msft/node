#ifndef SRC_NODE_CODE_INTEGRITY_H_
#define SRC_NODE_CODE_INTEGRITY_H_

#ifdef _WIN32

#include <Windows.h>

/* from winternl.h */
#if !defined(__UNICODE_STRING_DEFINED) && defined(__MINGW32__)
#define __UNICODE_STRING_DEFINED
#endif
typedef struct _UNICODE_STRING {
  USHORT Length;
  USHORT MaximumLength;
  PWSTR  Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

typedef const UNICODE_STRING *PCUNICODE_STRING;

// {0xb5367df1,0xcbac,0x11cf,{0x95,0xca,0x00,0x80,0x5f,0x48,0xa1,0x92}}
#define WLDP_HOST_OTHER \
    {0x626cbec3, 0xe1fa, 0x4227, {0x98, 0x0, 0xed, 0x21, 0x2, 0x74, 0xcf, 0x7c}};

//
// Enumeration types for WldpCanExecuteFile
//
typedef enum WLDP_EXECUTION_POLICY {
    WLDP_EXECUTION_POLICY_BLOCKED,
    WLDP_EXECUTION_POLICY_ALLOWED,
    WLDP_EXECUTION_POLICY_REQUIRE_SANDBOX,
} WLDP_EXECUTION_POLICY;

typedef enum WLDP_EXECUTION_EVALUATION_OPTIONS {
    WLDP_EXECUTION_EVALUATION_OPTION_NONE = 0x0,
    WLDP_EXECUTION_EVALUATION_OPTION_EXECUTE_IN_INTERACTIVE_SESSION = 0x1,
} WLDP_EXECUTION_EVALUATION_OPTIONS;

typedef HRESULT(WINAPI *pfnWldpCanExecuteFileFromDetachedSignature)(
    _In_ REFGUID host,
    _In_ WLDP_EXECUTION_EVALUATION_OPTIONS options,
    _In_ HANDLE contentFileHandle,
    _In_ HANDLE signatureFileHandle,
    _In_opt_ PCWSTR auditInfo,
    _Out_ WLDP_EXECUTION_POLICY *result
);

typedef HRESULT(WINAPI *pfnWldpGetApplicationSettingBoolean)(
    _In_ PCWSTR id,
    _In_ PCWSTR setting,
    _Out_ BOOL *result
    );

typedef enum WLDP_SECURE_SETTING_VALUE_TYPE
{
    WLDP_SECURE_SETTING_VALUE_TYPE_BOOLEAN = 0,
    WLDP_SECURE_SETTING_VALUE_TYPE_ULONG,
    WLDP_SECURE_SETTING_VALUE_TYPE_BINARY,
    WLDP_SECURE_SETTING_VALUE_TYPE_STRING
} WLDP_SECURE_SETTING_VALUE_TYPE, *PWLDP_SECURE_SETTING_VALUE_TYPE;

typedef HRESULT(WINAPI *pfnWldpQuerySecurityPolicy)(
    _In_ const UNICODE_STRING * providerName,
    _In_ const UNICODE_STRING * keyName,
    _In_ const UNICODE_STRING * valueName,
    _Out_ PWLDP_SECURE_SETTING_VALUE_TYPE valueType,
    _Out_writes_bytes_opt_(*valueSize) PVOID valueAddress,
    _Inout_ PULONG valueSize
    );

#ifndef DECLARE_CONST_UNICODE_STRING
#define DECLARE_CONST_UNICODE_STRING(_var, _string) \
const WCHAR _var ## _buffer[] = _string; \
__pragma(warning(push)) \
__pragma(warning(disable:4221)) __pragma(warning(disable:4204)) \
const UNICODE_STRING _var = { sizeof(_string) - sizeof(WCHAR), sizeof(_string), (PWCH) _var ## _buffer } \
__pragma(warning(pop))
#endif

#endif // _WIN32
#endif // SRC_NODE_CODE_INTEGRITY_H_
