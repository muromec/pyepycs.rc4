import epycs.rc4

rc4 = epycs.rc4.RC4(0x375F05CA)
print rc4.crypt("\xBA\xA4\x39\xCF\x8D\xD4\x0F\x91\xEB\x9C").encode('hex')
