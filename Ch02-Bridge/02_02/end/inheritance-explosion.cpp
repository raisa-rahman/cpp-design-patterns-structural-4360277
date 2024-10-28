#include <iostream>
#include <memory>  // Required for std::unique_ptr and std::make_unique
using namespace std;

class ITextShare { 
public: 
   virtual bool shareText(const string& text) = 0; 
   virtual ~ITextShare() = default;
}; 

class EmailShare : public ITextShare { 
public: 
   bool shareText(const string& text) override { 
     cout << "EmailShare::shareText() sharing text: " << text << endl;
     return true; 
   } 
};

class SMSShare : public ITextShare { 
public: 
   bool shareText(const string& text) override { 
     cout << "SMSShare::shareText() sharing text: " << text << endl;
     return true; 
   } 
};

class EmailShareEncrypted : public EmailShare
{
public:
   bool shareText(const string &text) override
   {
     cout << "EmailShareEncrypted::shareText() encrypting text..." << endl;
     string encrypted = xorEncrypt(text);     
     return EmailShare::shareText(encrypted);
   }

private:
   string xorEncrypt(const string &input)
   {
     char key = 64;
     string output = input;

     for (size_t i = 0; i < input.size(); ++i)  // Use size_t for index
         output[i] = input[i] ^ key;

     return output;
   }
};

class SMSShareEncrypted : public SMSShare
{
public:
   bool shareText(const string &text) override
   {
     cout << "SMSShareEncrypted::shareText() encrypting text..." << endl;
     string encrypted = xorEncrypt(text);     
     return SMSShare::shareText(encrypted);
   }

private:
   string xorEncrypt(const string &input)  // Changed to pass by const reference
   {
     char key = 64;
     string output = input;

     for (size_t i = 0; i < input.size(); ++i)  // Use size_t for index
         output[i] = input[i] ^ key;

     return output;
   }
};

class EmailShareAutoExpiring: public EmailShare
{
    // You can add the logic for auto-expiring email sharing here
};

class SMSShareAutoExpiring: public SMSShare
{
    // You can add the logic for auto-expiring SMS sharing here
};

int main()
{
    // Create an array of unique pointers to ITextShare objects.
    const std::unique_ptr<ITextShare> sharingServices[] =
    {
        std::make_unique<EmailShare>(),
        std::make_unique<SMSShare>(),
        std::make_unique<EmailShareEncrypted>(),
        std::make_unique<SMSShareEncrypted>()
    };

    // Share content using the services
    const string content = "Beam me up, Scotty!";
    for (const auto& service : sharingServices)
    {        
        service->shareText(content);
        cout << endl;
    }

    return 0;
}
