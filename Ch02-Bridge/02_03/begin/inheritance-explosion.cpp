#include <iostream>
#include <memory> // Include for smart pointers
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

class EmailShareEncrypted : public EmailShare {
public:
   bool shareText(const string &text) override {
     cout << "EmailShareEncrypted::shareText() encrypting text..." << endl;
     string encrypted = xorEncrypt(text);     
     return EmailShare::shareText(encrypted);
   }

private:
   string xorEncrypt(const string &input) {
     char key = 64;
     string output = input;

     for (size_t i = 0; i < input.size(); ++i) {
         output[i] = input[i] ^ key;
     }

     return output;
   }
};

class SMSShareEncrypted : public SMSShare {
public:
   bool shareText(const string &text) override {
     cout << "SMSShareEncrypted::shareText() encrypting text..." << endl;
     string encrypted = xorEncrypt(text);     
     return SMSShare::shareText(encrypted);
   }

private:
   string xorEncrypt(const string &input) { // Changed to const reference
     char key = 64;
     string output = input;

     for (size_t i = 0; i < input.size(); ++i) {
         output[i] = input[i] ^ key;
     }

     return output;
   }
};

// Placeholders for additional classes
class EmailShareAutoExpiring: public EmailShare {
    // Future implementation for auto-expiring feature...
};

class SMSShareAutoExpiring: public SMSShare {
    // Future implementation for auto-expiring feature...
};

int main() {
    // Create an array of pointers to ITextShare objects using smart pointers
    const unique_ptr<ITextShare> sharingServices[] = {
        make_unique<EmailShare>(),
        make_unique<SMSShare>(),
        make_unique<EmailShareEncrypted>(),
        make_unique<SMSShareEncrypted>()
    };

    const string content = "Beam me up, Scotty!";
    for (const auto& service : sharingServices) {        
        service->shareText(content);
        cout << endl;
    }

    return 0;
}
