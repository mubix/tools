# tools
Operational toolset utilizing git's submodule feature.

* Info on how this is being accomplished is here: http://git-scm.com/book/en/Git-Tools-Submodules
* Another good reference: http://chrisjean.com/2009/04/20/git-submodules-adding-using-removing-and-updating/

If you run your own repo, you can use: ```git submodule foreach git pull``` to keep each repo up to date.

### Get started

After you pulled the repo you'll notice that none of the "submodule" repos have any files in them.

To get sarted you need to perform the following:
* ```git submodule init``` - initialize the submodules
* ```git submodule update``` - pull & update the repos to current version

### Update

* ```git submodule update``` - update the repos to current version

