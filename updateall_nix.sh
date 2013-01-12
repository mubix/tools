#!/bin/bash

# Update nmap
cd nmap
svn up
cd ..
git add ./nmap/

# Update submodules
git submodule foreach git checkout master
git submodule foreach git pull
git commit -a -m 'updated submodules'

