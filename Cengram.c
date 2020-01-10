#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Cengram.h"


extern Node *userProfiles;
extern int totalUserCount;
extern Node *allPosts;
extern int totalPostCount;
int call_counter;

int profLen(Node *usrpfs)
{
    int count=0;
    while(usrpfs){
        usrpfs = usrpfs->next;
        count++;
    }
    return count;
}

void removeFromFollow(int userId)
{
    Node *temp_node;
    Node *temp_followers1;
    Node *temp_followers2;
    Node *prev;
    User *temp_user1;
    User *temp_user2;

    temp_node = userProfiles;
    while(temp_node->next){
        temp_user1 = temp_node->data;
        temp_followers1 = temp_user1->followers;
        prev=temp_followers1;

        while(temp_followers1){
            temp_user2=temp_followers1->data;
            if(userId == temp_user2->userId){
                temp_user1->numOfFollowers-=1;
                if(temp_followers1->next == NULL){
                    temp_followers1 = NULL;
                    free(temp_followers1);
                }
                else{
                    temp_followers2 = temp_followers1->next;
                    prev->next = temp_followers2;
                }
            }
            prev=temp_followers1;
            temp_followers1 = temp_followers1->next;
        }
        temp_node = temp_node->next;
    }
}

User *registerUser(int newUserId, char *newUsername, int birthdayDay, int birthdayMonth, int birthdayYear)
{
/* TODO: Implement this function */
    Node *temp;
    Node *new_node;
    char *temp_username;
    User *new_user;
    Date *new_date;


    new_node = (Node*)malloc(sizeof(Node));
    new_user = (User*)malloc(sizeof(User));
    new_date = (Date*)malloc(sizeof(Date));
    
    new_user->userId = newUserId;

    temp_username = (char*)malloc(sizeof(newUsername));
    strcpy(temp_username, newUsername);
    new_user->username = temp_username;

    new_date->day = birthdayDay;
    new_date->month = birthdayMonth;
    new_date->year = birthdayYear;
    new_user->birthday = new_date;
    
    new_node->data=new_user;

    temp=userProfiles;
    
    if(userProfiles == NULL){
        userProfiles = new_node;
        totalUserCount++;
        return new_user;
    }
    else{
        while(temp->next){
            temp=temp->next;
        }
    }
    temp->next=new_node; 
    totalUserCount++;

    return new_user;
}
    
void followUser(int userId1, int userId2)
{
    /* TODO: Implement this function */
    Node *userNode1, *userNode2;
    Node *temp_node;
    Node *f_node;
    User *temp_user;

    temp_node = userProfiles;
    while(temp_node){
        temp_user = temp_node->data;
        if(temp_user->userId == userId1){
            userNode1 = temp_node;
        }
        if(temp_user->userId == userId2){
            userNode2 = temp_node;
        }
        temp_node = temp_node->next;
    }
    temp_user = userNode2->data;
    if(temp_user->followers == NULL){
        f_node =(Node*)malloc(sizeof(Node));
        f_node->data = userNode1->data;
        temp_user->followers = f_node;
        (temp_user->numOfFollowers)++;
    }
    else{
        f_node = temp_user->followers;
        while(f_node->next){
            f_node = f_node->next;
        }
        f_node->next =(Node*)malloc(sizeof(Node));
        f_node->next->data = userNode1->data;
        temp_user->numOfFollowers++;
    }
}
   
Post *createPost(int postId, int ownerUserId, char *newContent)
{
    /* TODO: Implement this function */
    Node *temp_node;
    Node *newNode;
    Node *temp_pst;
    Node *all_posts;
    User *temp_user;
    Post *newPost;
    char *cont;

    temp_node=userProfiles;

    newPost = (Post*)malloc(sizeof(Post));
    newPost->postId = postId;
    while(temp_node->next)
    {
        temp_user = temp_node->data;

        if(temp_user->userId == ownerUserId)
        {
            newPost->author = temp_user;
            break;
        }

        temp_node = temp_node->next;

    }
    cont = (char *)malloc(sizeof(char) * strlen(newContent));
    strcpy(cont,newContent);
    newPost->content = cont;
    temp_user->numOfPosts += 1;

    temp_pst = temp_user->posts;
    
    newNode = (Node*)malloc(sizeof(Node));
    newNode->data = newPost;
    newNode->next = NULL;

    if(temp_user->posts == NULL)
    {
        temp_user->posts = newNode;
    }
    else
    { 
        while(temp_pst->next){
            temp_pst = temp_pst->next;
        }
        newNode = (Node*)malloc(sizeof(Node));
        newNode->data=newPost;
        (temp_pst->next) = newNode;
    }
    if(allPosts == NULL)
    {
        allPosts = (Node*)malloc(sizeof(Node));
        allPosts->data = newPost;
        allPosts->next = NULL;
    }
    else
    {
        all_posts = allPosts;
        while(all_posts->next){
            all_posts=all_posts->next;
        }
        newNode = (Node*)malloc(sizeof(Node));
        newNode->data=newPost;
        all_posts->next = newNode;
    }
    totalPostCount++;
    return newPost;
}

void removeUserAccount(int deletedUserId)
{
    /* TODO: Implement this function */

    Node *temp_node;     
 
    Node *temp_node1;   

    Node *temp_followers;

    User *temp_user;

    removeFromFollow(deletedUserId);
    temp_node = userProfiles;
    while(temp_node->next){
        temp_user=(temp_node->next)->data;
        if (temp_user->userId == deletedUserId)
        {
            if((temp_node->next)->next != NULL){
                temp_node->next = (temp_node->next)->next;
            }
            else{
                temp_node->next = NULL;
            }
            break;
        }
        temp_node = temp_node->next;
    }

    temp_followers = temp_user->followers;

    while(temp_followers != NULL && temp_followers->next)
    {
        temp_node1=temp_followers->next;
        if(temp_node1->next == NULL){
            temp_followers = NULL;
            free(temp_node1);
        }
        else{
            temp_followers=temp_node1->next;
            free(temp_node1);
        }
        free(temp_followers);
    }
    totalUserCount--;

}

