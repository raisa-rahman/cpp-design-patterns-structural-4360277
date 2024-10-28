#include <iostream>
#include <string>
#include <memory>
#include <ctime>
#include <random>

using namespace std;

// Abstract class representing cloud storage.
class CloudStorage
{
public:
    virtual bool uploadContents(const string &content) = 0;
    virtual int getFreeSpace() = 0;
    virtual ~CloudStorage() = default;
};

// CloudDrive class implementation.
class CloudDrive : public CloudStorage
{
public:
    virtual bool uploadContents(const string& content) override
    {
        cout << "Uploading " << content.length() << " bytes to CloudDrive: " << endl;
        return true;
    }

    virtual int getFreeSpace() override
    {
        // Use random number generator for free space simulation.
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, 20); // Random space between 0 and 20GB.

        int size = dis(gen);
        cout << "Available CloudDrive storage: " << size << "GB" << endl;
        return size;
    }
};

// FastShare class implementation.
class FastShare : public CloudStorage
{
public:
    virtual bool uploadContents(const string& content) override
    {
        cout << "Uploading " << content.length() << " bytes to FastShare: " << endl;
        return true;
    }

    virtual int getFreeSpace() override
    {
        // Use random number generator for free space simulation.
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, 10); // Random space between 0 and 10GB.

        int size = dis(gen);
        cout << "Available FastShare storage: " << size << "GB" << endl;
        return size;
    }    
};

// 3rd party service VirtualDrive.
class VirtualDrive
{
public:
    bool uploadData(const string& data, const int uniqueID)
    {
        cout << "Uploading to VirtualDrive: \"" << data << "\" ID: " << uniqueID << endl;
        return true;
    }

    int usedSpace()
    {
        // Use random number generator for used space simulation.
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, 10); // Used space between 0 and 10GB.

        return dis(gen);
    }

    static const int totalSpace = 15; // Total space is 15GB.
};

// Adapter for VirtualDrive to fit CloudStorage interface.
class VirtualDriveAdapter : public CloudStorage, private VirtualDrive
{
public:
    virtual bool uploadContents(const string& content) override
    {
        int uniqueID = generateUID(); // Generate a unique ID for this content.
        cout << "VirtualDriveAdapter::uploadContents() -> Calling VirtualDrive::uploadData()" << endl;
        return uploadData(content, uniqueID);
    }

    virtual int getFreeSpace() override
    {
        int available = totalSpace - usedSpace(); // Calculate available space.
        cout << "VirtualDriveAdapter::getFreeSpace() -> Available VirtualDrive storage: " << available << " GB" << endl;
        return available;
    }

private:
    // Generates a unique ID based on the current time.
    int generateUID()
    {
        const time_t result = time(nullptr); // Get current time in seconds since the Epoch.
        return static_cast<int>(result); // Return as an integer.
    }
};

// Main function.
int main()
{
    // Create an array of pointers to CloudStorage objects.
    const unique_ptr<CloudStorage> cloudServices[] = {
        make_unique<CloudDrive>(),
        make_unique<FastShare>(),
        make_unique<VirtualDriveAdapter>()
    };

    // Sample content to upload.
    const string content = "Beam me up, Scotty!";

    // Iterate through the array and invoke the uploadContents and getFreeSpace methods.
    for (const auto& service : cloudServices)
    {
        service->uploadContents(content);
        service->getFreeSpace();
        cout << endl;
    }

    return 0;
}
