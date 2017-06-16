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

package rai;
import inet.networklayer.common.InterfaceTable;
import rai.Ieee802154NarrowbandNicRssi;
import inet.mobility.contract.IMobility;
import inet.linklayer.contract.IWirelessNic;
//
// TODO auto-generated type
//
module Node802154
{
    parameters:
    @networkNode;

    string nicType = default("Ieee802154NarrowbandNicRssi");
    string mobilityType = default("StationaryMobility");
    *.mobilityModule = default(mobilityType != "" ? absPath(".mobility") : "");
    *.interfaceTableModule = default(absPath(".interfaceTable"));
   
    @statistic[E2E](record=vector);
    gates:
        input channelIn @loose;

    submodules:
        interfaceTable: InterfaceTable {
            @display("p=32,98");
        }
        app: ApplicationLayer {
            @display("p=170,37;i=-");
        }
        Network: NetworkLayer {
            @display("p=137,179");
        }
        iWirelessNic: <nicType> like IWirelessNic {
            @display("p=134,287");
            radio.transmitter.preambleDuration = 192us;
            radio.bandwidth = 2.8MHz;
        }

        mobility: <mobilityType> like IMobility {
            @display("p=32,37");
        }
    connections:
        channelIn --> iWirelessNic.radioIn;




       

        Network.UpperLayerOut --> app.lowerLayerIn;
        app.lowerLayerOut --> Network.upperLayerIn;

        iWirelessNic.upperLayerOut --> Network.LowerlayerIn;
        Network.LowerlayerOut --> iWirelessNic.upperLayerIn;
}
