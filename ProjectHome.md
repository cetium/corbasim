&lt;wiki:gadget url="http://www.ohloh.net/p/616667/widgets/project\_cocomo.xml" height="205" width="350" border="0"/&gt;

# Introduction #

corbasim is a generator of generic testing tools for CORBA-based applications. It generates this tools from the IDL files of the applications.

corbasim libraries might be used also as support libraries in the development of the CORBA-based applications.

![http://corbasim.googlecode.com/svn/trunk/doc/images/process.png](http://corbasim.googlecode.com/svn/trunk/doc/images/process.png)

## Hello world example ##

```
module HelloApp
{
  typedef sequence< string > Names;
  interface Hello
  {
    string sayHello();
    string sayHelloTo(in Names people);
    oneway void shutdown();
  };
}
```

Generating a client of this for the Hello interface:

```
$ ls
hello.idl
$ corbasim_idl -Gclient -Gserver hello.idl
$ ls
hello_adapted.hpp             hello.cmake       HelloApp_Hello_client_main.cpp 
HelloApp_Hello_server.cpp     hello.idl
```

Just compile this files and here is it:

![http://corbasim.googlecode.com/svn/trunk/doc/images/hello_client.png](http://corbasim.googlecode.com/svn/trunk/doc/images/hello_client.png)

# Generated tools #
  * A GUI client with scripting support.
  * A script re-player.
  * A dummy server that records any incoming call.

# CORBASIM libraries #
## JSON serializer ##

```
struct St
{
    sequence< long > l;
    long b;
};
```

Parsing it from JSON:

```
St my_st;
bool res = corbasim::json::parse(my_st, "{\"l\": [0,1,2,3,4,5], \"b\": 1560}");
```

Serializing into JSON format:

```
corbasim::json::write(std::cout, my_st); 
```

# CORBASIM, CORBA and C++ Metaprogramming #

The main CORBASIM generated file is the _adapted_ file, that allows to use some metafunctions with the types defined in the IDL files. This metafunctions allows to write generic code. For example, the GUI interfaces in this tools are generated in compile-time by this way, with a metafunction widget< T >. For each type T, widget< T > is a helper for creating instances of the widget type asociated to T.

# Requeriments #

  * Boost C++ Libraries (1.45.0 or greater)
  * Qt (4.2 or greater, just for GUI tools)
  * ACE TAO (will support other ORBs)

# Instalation #

  1. Download the source code from the repository
  1. Run the bootstrap script
  1. Run make and make install into build directory