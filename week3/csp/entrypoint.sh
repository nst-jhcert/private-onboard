#!/bin/bash
cd /app/libcsp
python3 ./examples/buildall.py

cd /app/parser
make test

chmod 600 /root/.ssh/authorized_keys
chown root:root /root/.ssh/authorized_keys
exec /usr/sbin/sshd -D