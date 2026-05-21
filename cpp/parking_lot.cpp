#include<bits/stdc++.h>
using namespace std;

enum class VehicleType{
    TwoWheeler,
    FourWheelerCompact,
    FourWheelerLarge,
    Truck
};

enum class VehicleSize{
    xs,
    s,
    m,
    l,
    xl,
    xxl
};

class VehicleInfo{
    VehicleType vehicle_type;
    VehicleSize vehicle_size;
};

class TimeGenerator{
    virtual chrono::time_point<chrono::system_clock>getTime() = 0;
};

class ITicket{
    chrono::time_point<chrono::system_clock>curr_time;
    VehicleInfo vehicle_info;
};

class IParkingSlot{
    unique_ptr<VehicleInfo>slot_options;
};

class IParkingSpace{
    virtual string getAddress() = 0;
    virtual unique_ptr<IParkingSlot>setAvailableSlots() = 0;
    virtual unique_ptr<IParkingSlot>getAvailableSlots() = 0;
   
};

enum class PaymentMethods{
    Cash,
    Card,
    UPI,
    Paypal
};

class IPaymentStrategy{
    PaymentMethods payment_method;
    virtual bool getPaymentStatus() = 0;
};

class MyParkingSpace : public IParkingSpace{
    private:
        const string name="";
    public: 
    MyParkingSpace(){
        this.name =  "address";
    }
    string getAddress() override{
        return "Ye le mera address";
    }
    unique_ptr<IParkingSlot>setAvailableSlots() override{
        return {small: {}}
    }
};

class ParkingServiceManager{
    VehicleType getVehicleType(){};
    VehicleSize getVehicleSize(){};
    double getAmountFromChart(VehicleSize &vehicle_size, VehicleType & vehicle_type, chrono::time_point<chrono::system_clock>& curr_time);
    myParkingSpace currSpaces(); // set slots, get slots
    // also add slot booking logic
    ITicket generateTicket();
    IPaymentStrategy paymentkar();
    // use above objects payments status to find if i should allow this to exit
};

int main(){

}