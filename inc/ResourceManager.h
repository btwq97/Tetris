#pragma once
//http://eangogamedevelopment.blogspot.com/2017/01/part-21-completing-game-menu.html

#include <unordered_map>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

template <typename Derived, class T>

class ResourceManager
{
public:
    ResourceManager(const std::string& fileName)
    {
        PopulateStorage(fileName);    //allocate resources on the heap
    }

    bool AddResource(const std::string& resourceName)
    {
        auto res = Find(resourceName); //see if resource is already allocated

        if (res) //if resourceName already allocated
        {
            ++res->second;  //increments counter in map
            return true;
        }

        auto filePath = fileMap.find(resourceName);

        if (filePath == fileMap.end())  //if we don't find resource in our container
            return false;

        T* resource = Load(filePath->second);

        if (!resource)      //if resource doesn't load
            return false;


        //if pass all tests we place resource on our container keeping track of allocatoin of memory.
        resourceMap.emplace(resourceName, std::make_pair(resource, 1));

        return true;
    }


    T* GetResource(const std::string& resourceName)
    {
        auto res = Find(resourceName); //use auto since we don't know what data-type the Find() method will return!

        if (res)
            return res->first;
        else
            return NULL;
    }



    bool ReleaseResource(const std::string& resourceName)
    {
        auto res = Find(resourceName);

        if (!res)
            return false;
        --res->second;  //decrement use counter if resource if found

        if (!res->second)
            Unload(resourceName);   //de-allocate memory

        return true;
    }

    //kill all resources
    void KillResources()
    {
        while (resourceMap.begin() != resourceMap.end())
        {
            delete resourceMap.begin()->second.first;
            resourceMap.erase(resourceMap.begin());
        }

    }

    T* Load(const std::string& path)
    {
        return static_cast<Derived*>(this)->Load(path);
    }

    ~ResourceManager()
    {
        KillResources();    //de-allocate the resources from the heap.
    }


private:

    std::unordered_map< std::string, std::pair<T*, int> > resourceMap; //string with pair of a Resource type + counter

    std::unordered_map<std::string, std::string> fileMap;   //stores all resources at intialization of instance

    std::pair<T*, int>* Find(const std::string& resourceName)
    {
        auto itr = resourceMap.find(resourceName);

        if (itr != resourceMap.end())
            return &itr->second;
        else
            return NULL;
    }

    void Unload(const std::string& resourceName)
    {
        auto itr = resourceMap.find(resourceName);

        if (itr == resourceMap.end())
        {
            std::cerr << "Fail" << std::endl;
            return;
        }
        delete itr->second.first;
        resourceMap.erase(itr);
    }


    void PopulateStorage(const std::string& fileName)
    {
        std::ifstream paths(fileName);

        if (paths.is_open())
        {
            std::string pathName;
            std::string path;

            while (!paths.eof())
            {
                paths >> pathName >> path;
                fileMap.emplace(pathName, path);

            }

            paths.close();
            return;

        }

        std::cerr << "Fail" << std::endl;
    }

};