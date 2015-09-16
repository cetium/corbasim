# How to compile CORBASIM with Microsoft Visual C++ Express 2010 #
## Installing dependencies ##
  1. Download and install Microsoft Visual C++ Express 2010. It is available from:
> > http://www.microsoft.com/visualstudio/en-us/products/2010-editions/visual-cpp-express
  1. Download the latest version of Boost C++ libraries from:
> > http://www.boost.org
> > You can find here how to compile them with Microsoft Visual C++ Express 2010:
> > > http://stackoverflow.com/questions/2629421/how-to-use-boost-in-visual-studio-2010

> > Or you can use an installer from BoostPro:
> > > http://www.boostpro.com/download/
  1. Download and install Qt Libraries from:

> > http://qt.nokia.com/downloads/
  1. If you want Python scripting support you have to install Python for Windows. It is available from:
> > http://www.python.org/download/
  1. ACE+TAO.
> > Download an ACE+TAO tarball containing a Microsoft Visual C++ Express 2010 project from:
> > > http://download.dre.vanderbilt.edu/
      1. Unzip the downloaded package, for example at C:\ACE\_wrappers
      1. Append C:\ACE\_wrappers\bin and C:\ACE\_wrappers\lib to your Path environment variable.

> > I don't know the first version of ACE+TAO with a project for Microsoft Visual C++ Express 2010. I used the latest version (6.0.5). Here are the instructions to compile them with mscv-10:
> > > http://www.dre.vanderbilt.edu/~schmidt/DOC_ROOT/ACE/ACE-INSTALL.html#msvc
  1. There is still no corbasim packaged distribution, so you will need download corbasim source code from the SVN repository. You may use TortoiseSVN, available from:

> > http://tortoisesvn.net/downloads.html

## Compiling corbasim ##

  1. Checkout corbasim source code.

# Pending tasks #

  1. Write an executable script to run corbasim idl compiler on Windows.