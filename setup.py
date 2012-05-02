from distutils.core import setup, Extension

setup(name="epycs.rc4", version="0.1",
      ext_modules=[
         Extension("epycs.rc4", 
             sources=[
		"rc4module.c",
		"crc32_util.c",
		"skype_rc4.c",	
	     ]
         ),
         ])
