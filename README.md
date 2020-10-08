
# Short description
**CEVProjectSettings** - plugin for CRYENGINE V allowing you easy configure you project settings from Sandbox

**Features :** 
* Automatic project file backup befory save any changes
* Update project settings at runtime and save it to .cryproject file
* Automatic Sandbox restart if you changes needed it


# Building
## Before compiling
* Download full source code from official <a href=https://github.com/CRYTEK/CRYENGINE/releases>CRYENGINE repository</a>
* Copy CEVProjectSettings sources to  `CRYENGINE/Code/CryPlugins/CEVProjectSettings `
* Add CEVProjectSettings module to `CRYENGINE/Code/CryPlugins/CMakeLists.txt `
```
add_subdirectory(CEVProjectSettings/Module)
```
## Compiling
* Generate CRYENGINE solution, select CEVProjectSettings target and compile it

# Using
* Copy ` CEVProjectSettings.dll ` to `CRYENGINE/bin/win_x64/EditorPlugins` folder


# GitHub community

I will be happy with any help from the community, so I'm waiting for your pull requests 

If you have any problem with this plugin please use [GitHub issues](https://github.com/afrostalin/CEVProjectSettings/issues) mechanism

# Contacts

If you need more from me, write me directly to my email : chernecoff@gmail.com

# Disclaimer
This is a third party plugin which has not been developed nor is being maintained by Crytek.