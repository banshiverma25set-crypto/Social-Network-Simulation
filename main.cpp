#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// ================= BASE USER CLASS =================
class User {
protected:
    string username;
    int trustScore;

public:
    User(string uname) {
        username = uname;
        trustScore = 50;
    }

    virtual void displayUser() {
        cout << "User: " << username << endl;
        cout << "Trust Score: " << trustScore << endl;
    }

    string getUsername() { return username; }

    int getTrustScore() { return trustScore; }

    void increaseTrust() { trustScore += 5; }

    void decreaseTrust() { trustScore -= 10; }

    virtual ~User() {}
};

// ================= VERIFIED USER (INHERITANCE) =================
class VerifiedUser : public User {
public:
    VerifiedUser(string uname) : User(uname) {
        trustScore = 80;
    }

    void displayUser() override {
        cout << "[Verified] User: " << username << endl;
        cout << "Trust Score: " << trustScore << endl;
    }
};

// ================= POST CLASS =================
class Post {
private:
    string content;
    string emotion;
    bool toxic;

public:
    Post(string text) {
        content = text;
        emotion = "Neutral";
        toxic = false;
    }

    void setEmotion(string e) { emotion = e; }

    void setToxic(bool t) { toxic = t; }

    string getContent() { return content; }

    string getEmotion() { return emotion; }

    bool isToxic() { return toxic; }

    void displayPost() {
        cout << "Post: " << content << endl;
        cout << "Emotion: " << emotion << endl;
        cout << "Toxic: " << (toxic ? "YES" : "NO") << endl;
        cout << "---------------------" << endl;
    }
};

// ================= AI ENGINE =================
class AIEngine {
public:
    string detectEmotion(string text) {
        if (text.find("happy") != string::npos ||
            text.find("great") != string::npos)
            return "Positive";

        if (text.find("sad") != string::npos ||
            text.find("bad") != string::npos)
            return "Negative";

        return "Neutral";
    }

    bool detectToxic(string text) {
        if (text.find("hate") != string::npos ||
            text.find("stupid") != string::npos)
            return true;

        return false;
    }
};

// ================= SOCIAL NETWORK SYSTEM =================
class SocialNetwork {
private:
    vector<User*> users;
    vector<Post> posts;
    AIEngine ai;

public:
    void registerUser() {
        string name;
        int type;

        cout << "Enter Username: ";
        cin >> name;

        cout << "1. Normal User\n2. Verified User\nChoice: ";
        cin >> type;

        if (type == 2)
            users.push_back(new VerifiedUser(name));
        else
            users.push_back(new User(name));

        cout << "User Registered Successfully!\n";
    }

    void showUsers() {
        for (auto u : users) {
            u->displayUser();
            cout << endl;
        }
    }

    void createPost() {
        cin.ignore();
        string text;

        cout << "Enter Post Content: ";
        getline(cin, text);

        Post p(text);

        string emotion = ai.detectEmotion(text);
        bool toxic = ai.detectToxic(text);

        p.setEmotion(emotion);
        p.setToxic(toxic);

        posts.push_back(p);

        if (toxic && !users.empty())
            users.back()->decreaseTrust();
        else if (!users.empty())
            users.back()->increaseTrust();

        cout << "Post Added!\n";
    }

    void showAllPosts() {
        for (auto &p : posts)
            p.displayPost();
    }

    void emotionFeed(string emo) {
        cout << "\n=== Emotion Based Feed ===\n";
        for (auto &p : posts) {
            if (p.getEmotion() == emo)
                p.displayPost();
        }
    }

    void goalBasedFeed() {
        cout << "\n=== Goal Based Feed (Positive Only) ===\n";
        for (auto &p : posts) {
            if (p.getEmotion() == "Positive" && !p.isToxic())
                p.displayPost();
        }
    }

    ~SocialNetwork() {
        for (auto u : users)
            delete u;
    }
};

// ================= MAIN MENU =================
int main() {
    SocialNetwork sn;
    int choice;

    do {
        cout << "\n===== AI SOCIAL NETWORK =====\n";
        cout << "1. Register User\n";
        cout << "2. Show Users\n";
        cout << "3. Create Post\n";
        cout << "4. Show All Posts\n";
        cout << "5. Emotion Feed\n";
        cout << "6. Goal Based Feed\n";
        cout << "0. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            sn.registerUser();
            break;

        case 2:
            sn.showUsers();
            break;

        case 3:
            sn.createPost();
            break;

        case 4:
            sn.showAllPosts();
            break;

        case 5: {
            string e;
            cout << "Enter Emotion (Positive/Negative/Neutral): ";
            cin >> e;
            sn.emotionFeed(e);
            break;
        }

        case 6:
            sn.goalBasedFeed();
            break;

        case 0:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid Choice\n";
        }

    } while (choice != 0);

    return 0;
}