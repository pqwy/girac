#include <girepository.h>
#include <string.h>
#include <stdio.h>
#include <dlfcn.h>
#include <ffi.h>

void dump_object(GIObjectInfo *info) {
  puts(g_object_info_get_type_name(info));
  int mtds = g_object_info_get_n_methods(info);
  printf("mtds: %d\n", mtds);
  for(int i = 0; i < mtds; ++i) {
    GICallableInfo *callable = g_object_info_get_method(info, i);
    puts(g_function_info_get_symbol(callable));
    if(GI_FUNCTION_IS_CONSTRUCTOR == g_function_info_get_flags(callable))
      puts("ctor");
    int args = g_callable_info_get_n_args(callable);
    printf("args: %d\n", args);
    for(int j = 0; j < args; ++j) {
      GIArgInfo *arg = g_callable_info_get_arg(callable, j);
      GITypeInfo *ty = g_arg_info_get_type(arg);
      printf("arg: %d, type: %s%s\n",
	     j,
	     g_type_tag_to_string(g_type_info_get_tag(ty)),
	     g_type_info_is_pointer(ty) ? "*" : "");
    }
  }
}

void dump_base_info(GIBaseInfo *info) {
  puts(g_base_info_get_name(info));
  if(GI_INFO_TYPE_OBJECT == (g_base_info_get_type(info)))
    dump_object((GIObjectInfo*)info);
  else puts("skip");
  puts("");
}

void test_call(void* lib) {
  void* ctor = dlsym(lib, "lg_button_new");
  void* tostr = dlsym(lib, "lg_component_to_string");
  if(!ctor || !tostr) puts("dlsym failed");
  
  ffi_cif ctorff;
  if(FFI_OK != ffi_prep_cif
     (&ctorff, FFI_DEFAULT_ABI, 0, &ffi_type_pointer, NULL)) {
    puts("problem");
    return;
  }

  void *btn;
  ffi_call(&ctorff, ctor, &btn, NULL);

  ///  
  ffi_cif tostrff;
  ffi_type *args[2];
  args[0] = args[1] = &ffi_type_pointer;
  
  if(FFI_OK != ffi_prep_cif
     (&tostrff, FFI_DEFAULT_ABI, 2, &ffi_type_uint, args)) {
    puts("problem 2");
    return;
  }

  char buff[1024];
  char *s;
  void *val[2];
  val[0] = &btn;
  val[1] = &s;
  s = buff;
  int len;
  ffi_call(&tostrff, tostr, &len, val);
  printf("len: %d, val: %s\n", len, buff);
}

int main() {
  g_type_init();

  g_irepository_prepend_search_path("/home/aka/devel/snippets/c/gobj/lg/code");
  GError *err = NULL;
  GITypelib *tl = g_irepository_require(NULL,
					"Lg", NULL,
					0, &err);
  if(!tl || err) {
    puts("fail");
    return -1;
  }
  const char* soname = g_irepository_get_shared_library(NULL, "Lg");
  printf("loading %s ... ", soname);
  void *lib = dlopen(soname, RTLD_NOW);
  if(!lib) {
    puts("load failed");
    return -1;
  }
  puts("loaded");

  printf("entries: %d\n\n", g_irepository_get_n_infos(NULL, "Lg"));  
  for(int i = 0;i < g_irepository_get_n_infos(NULL, "Lg"); ++i)
    dump_base_info(g_irepository_get_info(NULL, "Lg", i));

  test_call(lib);

  return 0;
}
