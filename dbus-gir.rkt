#lang racket

'(repository (c:identifier-prefixes "DBus"
              c:symbol-prefixes "DBus")
  (include (name "GObject"
            version "2.0"))
  (package (name "dbus-glib-1"))
  (namespace (name "DBusGLib"
              version "1.0"
              c:prefix "DBusG")
    (record (name "Connection"
             c:type "DBusGConnection"))
    (record (name "MethodInvocation"
             c:type "DBusGMethodInvocation"))
    (class (name "Proxy"
            c:type "DBusGProxy"
            parent "GObject.Object"
            glib:type-name "DBusGProxy"
            glib:get-type "dbus_g_proxy_get_type"))
    (record (name "ProxyClass"
             c:type "DBusGProxyClass"))))

'(repository (c:identifier-prefixes "DBus"
	      c:symbol-prefixes "DBus")
  (package name "dbus-1")
  (namespace (name "DBus"
              version "1.0"
              c:prefix "DBus")
    (enumeration (name "BusType"
                  c:type "DBusBusType")
      (member (name "session"
               value "0"
               c:identifier "DBUS_BUS_SESSION"))
      (member (name "system"
               value "1"
               c:identifier "DBUS_BUS_SYSTEM"))
      (member (name "starter"
               value "2"
               c:identifier "DBUS_BUS_STARTER")))
    (record (name "Connection"
             c:type "DBusConnection"
             glib:type-name "DBusConnection"
             glib:get-type "dbus_connection_get_type"))
    (record (name "Error"
             c:type "DBusError"))
    (record (name "Message"
             c:type "DBusMessage"))
    (record (name "MessageIter"
             c:type "DBusMessageIter"))
    (record (name "PendingCall"
             c:type "DBusPendingCall"))))


