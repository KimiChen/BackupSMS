如果编译调试，请上传相关源代码
make
ldid -S bsms
chmod +x bsms
./bsms


如果是直接安装，请按照顺序执行
cp libcurl.4.dylib /usr/lib/
cp libcurl.la /usr/lib/
ln -s /usr/lib/libcurl.4.dylib /usr/lib/libcurl.dylib
chmod +x bsms
./bsms#看是否能够正常输出bsms start，然后继续执行

cp bsms /usr/libexec/cydia/bsms
cp com.bsms.bsms.plist /System/Library/LaunchDaemons/com.bsms.bsms.plist
chown root:wheel /System/Library/LaunchDaemons/com.bsms.bsms.plist
chmod 644 /System/Library/LaunchDaemons/com.bsms.bsms.plist
ls -al /usr/libexec/cydia/bsms
ls -al /System/Library/LaunchDaemons/com.bsms.bsms.plist

reboot
