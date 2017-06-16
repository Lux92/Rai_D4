//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package rai.simulations;
import inet.node.inet.WirelessHost;
import inet.physicallayer.ieee802154.packetlevel.Ieee802154NarrowbandScalarRadioMedium;
import inet.physicallayer.propagation.ConstantTimePropagation;
import rai.Node802154;

//
// TODO auto-generated type
//
network Test
{ @display("bgb=200,200");
    int numNodes;
    
    submodules:
        radioMedium: Ieee802154NarrowbandScalarRadioMedium {
            @display("p=0,0");
        }
        node[numNodes]: Node802154 {
            
        }
        
    connections allowunconnected:
}
