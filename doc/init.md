Sample init scripts and service configuration for slated
==========================================================

Sample scripts and configuration files for systemd, Upstart and OpenRC
can be found in the contrib/init folder.

    contrib/init/slated.service:    systemd service unit configuration
    contrib/init/slated.openrc:     OpenRC compatible SysV style init script
    contrib/init/slated.openrcconf: OpenRC conf.d file
    contrib/init/slated.conf:       Upstart service configuration file
    contrib/init/slated.init:       CentOS compatible SysV style init script

1. Service User
---------------------------------

All three startup configurations assume the existence of a "slate" user
and group.  They must be created before attempting to use these scripts.

2. Configuration
---------------------------------

At a bare minimum, slated requires that the rpcpassword setting be set
when running as a daemon.  If the configuration file does not exist or this
setting is not set, slated will shutdown promptly after startup.

This password does not have to be remembered or typed as it is mostly used
as a fixed token that slated and client programs read from the configuration
file, however it is recommended that a strong and secure password be used
as this password is security critical to securing the wallet should the
wallet be enabled.

If slated is run with "-daemon" flag, and no rpcpassword is set, it will
print a randomly generated suitable password to stderr.  You can also
generate one from the shell yourself like this:

bash -c 'tr -dc a-zA-Z0-9 < /dev/urandom | head -c32 && echo'

Once you have a password in hand, set rpcpassword= in /etc/slate/slate.conf

For an example configuration file that describes the configuration settings,
see contrib/debian/examples/slate.conf.

3. Paths
---------------------------------

All three configurations assume several paths that might need to be adjusted.

Binary:              /usr/bin/slated
Configuration file:  /etc/slate/slate.conf
Data directory:      /var/lib/slated
PID file:            /var/run/slated/slated.pid (OpenRC and Upstart)
                     /var/lib/slated/slated.pid (systemd)

The configuration file, PID directory (if applicable) and data directory
should all be owned by the slate user and group.  It is advised for security
reasons to make the configuration file and data directory only readable by the
slate user and group.  Access to slate-cli and other slated rpc clients
can then be controlled by group membership.

4. Installing Service Configuration
-----------------------------------

4a) systemd

Installing this .service file consists on just copying it to
/usr/lib/systemd/system directory, followed by the command
"systemctl daemon-reload" in order to update running systemd configuration.

To test, run "systemctl start slated" and to enable for system startup run
"systemctl enable slated"

4b) OpenRC

Rename slated.openrc to slated and drop it in /etc/init.d.  Double
check ownership and permissions and make it executable.  Test it with
"/etc/init.d/slated start" and configure it to run on startup with
"rc-update add slated"

4c) Upstart (for Debian/Ubuntu based distributions)

Drop slated.conf in /etc/init.  Test by running "service slated start"
it will automatically start on reboot.

NOTE: This script is incompatible with CentOS 5 and Amazon Linux 2014 as they
use old versions of Upstart and do not supply the start-stop-daemon uitility.

4d) CentOS

Copy slated.init to /etc/init.d/slated. Test by running "service slated start".

Using this script, you can adjust the path and flags to the slated program by
setting the SLATED and FLAGS environment variables in the file
/etc/sysconfig/slated. You can also use the DAEMONOPTS environment variable here.

5. Auto-respawn
-----------------------------------

Auto respawning is currently only configured for Upstart and systemd.
Reasonable defaults have been chosen but YMMV.
