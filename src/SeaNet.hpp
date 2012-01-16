#ifndef _SEANET_H_
#define _SEANET_H_ 

#include <iodrivers_base/Driver.hpp>
#include "SeaNetTypes.hpp"

namespace sea_net {
class SeaNetPacket;

class SeaNet : protected ::iodrivers_base::Driver
{
public:
        /** Base class for RS232 SeaNet devices
         *  The class has to be initialized with 
         *  the right device type which is used
         *  as communictaion check
         */ 
	SeaNet(const DeviceType type);
	~SeaNet();

        /** Opens a serial port and sets it up to a sane configuration.
         *
         * Throws UnixError on error */
        void openSerial(std::string const& port, int baudrate, int timeout);

        /** Clears the input buffer and triggers the device to send 
         *  mtHeadData 
         *
         * Throws UnixError on error */
        void start();

        /** Reboots the Device and waits for a mtAlive package */
        void reboot(int timeout);

        /** Reads one packat from the input buffer and returns its type.
         *  Use getAuxData, getVersion ... depending on the returned type
         *  to get the content of the package */
        PacketType readPacket(int timeout);

        /** gives a reference to the raw data read by readPacket */
        void getRawData(const uint8_t* &buffer, size_t &size);
        
        /** extracts the payload from a mtAux package 
         *
         *  call this function if readPacket returns mtAuxData */  
        void getAuxData(std::vector<uint8_t> &data);

        /** extracts the software version of the device from a mtVersionData package 
         *
         *  call this function if readPacket returns mtVersionData */  
        void getVersion(VersionData &version, int timeout);

protected:
        void writeSendData(int timeout);
        virtual int extractPacket(uint8_t const* buffer, size_t buffer_size) const;
        SeaNetPacket* getSeaNetPacket();

private:	
        DeviceType device_type;
        SeaNetPacket* sea_net_packet;
}; };
#endif

