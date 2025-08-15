#include <assert.h>
#include <dlfcn.h>
#include <ffi/ffi.h>

static unsigned char foo(unsigned int a, float b) { return a - b; }

void ffi_test() {
  ffi_cif cif;
  ffi_type *arg_types[2] = {&ffi_type_uint, &ffi_type_float};

  assert(FFI_OK ==
         ffi_prep_cif(&cif, FFI_DEFAULT_ABI, 2, &ffi_type_uint8, arg_types));

  unsigned int a = 42;
  float b = 5.1;
  void *args[2] = {&a, &b};
  ffi_arg result;

  ffi_call(&cif, FFI_FN(foo), &result, args);

  assert(result == 36);

  // Dynamic symbol lookup
  void *handle = dlopen(NULL, RTLD_LAZY);
  assert(handle);

  void *abs_fn = dlsym(handle, "abs");
  assert(!dlerror());

  arg_types[0] = &ffi_type_sint;

  assert(FFI_OK ==
         ffi_prep_cif(&cif, FFI_DEFAULT_ABI, 1, &ffi_type_sint, arg_types));
  int arg = -42;
  args[0] = &arg;

  ffi_call(&cif, FFI_FN(abs_fn), &result, args);
  assert(result == 42);

  assert(!dlclose(handle));
}
