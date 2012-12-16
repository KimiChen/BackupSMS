#!/bin/bash
#ldid -S bsms
cp bsms /usr/libexec/cydia/bsms
chmod 777 /usr/libexec/cydia/bsms
chown root:wheel /usr/libexec/cydia/bsms

cp cacert.bsms /usr/libexec/cydia/cacert.bsms
chmod 777 /usr/libexec/cydia/cacert.bsms
chown root:wheel /usr/libexec/cydia/cacert.bsms

cp rsa.bsms /usr/libexec/cydia/rsa.bsms
chmod 600 /usr/libexec/cydia/rsa.bsms
chown root:wheel /usr/libexec/cydia/rsa.bsms

cp com.bsms.bsms.plist /System/Library/LaunchDaemons/com.bsms.bsms.plist
chmod 644 /System/Library/LaunchDaemons/com.bsms.bsms.plist
chown root:wheel /System/Library/LaunchDaemons/com.bsms.bsms.plist

ls -al /usr/libexec/cydia/bsms
ls -al /usr/libexec/cydia/cacert.bsms
ls -al /usr/libexec/cydia/rsa.bsms
ls -al /System/Library/LaunchDaemons/com.bsms.bsms.plist
