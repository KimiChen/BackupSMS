#!/bin/bash
#gcc -o bsms bsms.c -l sqlite3 -L /usr/lib/libsqlite3.dylib /usr/lib/libcurl.4.dylib && ldid -S bsms && ./bsms
cp bsms /usr/libexec/cydia/bsms
cp com.bsms.bsms.plist /System/Library/LaunchDaemons/com.bsms.bsms.plist
chown root:wheel /System/Library/LaunchDaemons/com.bsms.bsms.plist
chmod 644 /System/Library/LaunchDaemons/com.bsms.bsms.plist
ls -al /usr/libexec/cydia/bsms
ls -al /System/Library/LaunchDaemons/com.bsms.bsms.plist