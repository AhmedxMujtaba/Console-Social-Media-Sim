#include "DoubleLinkedList.hpp"
#include "User.hpp"

class ForYouPage {
private:
    DoubleLinkedList<Post> postsToDisplay;
    DoubleLinkedList<User> friends;

public:
    
    ForYouPage(DoubleLinkedList<User> friends) {
        this->friends = friends;
    }

 
    DoubleLinkedList<Post> getPostsToDisplay() const {
        return postsToDisplay;
    }

    
    void setPostsToDisplay(const DoubleLinkedList<Post>& posts) {
        postsToDisplay = posts;
    }

 
    DoubleLinkedList<User> getFriends() const {
        return friends;
    }


    void setFriends(const DoubleLinkedList<User>& friendsList) {
        friends = friendsList;
    }
};
