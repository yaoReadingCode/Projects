from pox.core import core

# You can check if IP is in subnet with 
# IPAddress("192.168.0.1") in IPNetwork("192.168.0.0/24")
# install with:
# sudo apt install python-netaddr
from netaddr import IPNetwork, IPAddress

import pox.openflow.libopenflow_01 as of

log = core.getLogger()

class Routing (object):
  def __init__ (self, connection):
    # Keep track of the connection to the switch so that we can
    # send it messages!
    self.connection = connection

    # This binds our PacketIn event listener
    connection.addListeners(self)

  def do_routing (self, packet, packet_in, port_on_switch, switch_id):
    # port_on_swtich - the port on which this packet was received
    # switch_id - the switch which received this packet

    # Your code here
    ICMP = packet.find('icmp')
    TCP = packet.find('tcp')
    IPV4 = packet.find('ipv4')
    ip_header = packet.find('ipv4')
    if IPV4:
      src = ip_header.srcip
      dst = ip_header.dstip
    C1 = '10.0.1.1'
    C2 = '10.0.1.2'
    C3 = '10.0.2.1'
    C4 = '10.0.2.2'
    C5 = '10.0.3.1'

    if ICMP or TCP:
      if TCP:
        if (switch_id == 1):
          if (dst == C1):
            end_port = 11
          elif (dst == C2):
            end_port = 12
          elif ((dst == C3) or (dst == C4)):
            end_port = 1
        elif (switch_id == 2):
          if (dst == C3):
            end_port = 11
          elif (dst == C4):
            end_port = 12
          elif ((dst == C1) or (dst == C2)):
            end_port = 1
      
      if ICMP:
        if (switch_id == 1):
          if (dst == C1):
            end_port = 11
          elif (dst == C2):
            end_port = 12
          elif (dst == C5):
            end_port = 2
        elif (switch_id == 3):
          if (dst == C5):
            end_port = 11
          elif ((dst == C1) or (dst == C2)):
            end_port = 2
      
      msg = of.ofp_flow_mod()
      msg.match = of.ofp_match.from_packet(packet)
      msg.idle_timeout = 50
      msg.hard_timeout = 50
      msg.actions.append(of.ofp_action_output(port = end_port))
      msg.data = packet_in
      self.connection.send(msg)
    pass

  def _handle_PacketIn (self, event):
    packet = event.parsed # This is the parsed packet data.
    if not packet.parsed:
      log.warning("Ignoring incomplete packet")
      return

    packet_in = event.ofp # The actual ofp_packet_in message.
    self.do_routing(packet, packet_in, event.port, event.dpid)

def launch ():
  def start_switch (event):
    log.debug("Controlling %s" % (event.connection,))
    Routing(event.connection)
  core.openflow.addListenerByName("ConnectionUp", start_switch)
