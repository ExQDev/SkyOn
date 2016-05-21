# SkyOn
SkyOn is an free multiplayer mod for TES V: Skyrim. Written on C++ using ScriptDragon by Alexander Blade, latest ver of Skyrim and SD: 1.9.32.0.8. 
Used VS 2015 Community and Boost lib ver 1.6.0(If you want change source, you need individually unpack & prepare boost libs)

SkyOn created for open editing and developing. You can contact to admin for joining us. SkyOn is open-source, but is very raw. You can help us!

If you want to edit this project, you need unpack, prepare and link Boost 1_6_0 libraries individually. Archive included, placed in "Boost" directory.

We`re using boost::asio & tcp protocol for connection. Server is individual program, wich can be runned on any Windows machine. Client is ASI file, it uses ScriptDagon to inject multiplayer in Skyrim. Both, Server & Client uses same resource for transport data - SkyOn Data library. Also, there is SkyOn Configurer project for easy configuring SkyOn.
