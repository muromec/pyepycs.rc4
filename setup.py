from distutils.core import setup, Extension

setup(name="epycs.rc4", version="0.1",
      packages = ['epycs'],
      ext_modules=[
         Extension("epycs.rc4", 
             sources=[
		"epycs/rc4module.c",
		"epycs/crc32_util.c",
		"epycs/skype_rc4.c",	
	     ]
         ),
         ])
