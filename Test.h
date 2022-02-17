#pragma once

#include <gtest/gtest.h>
#include "Project1.h"

class TestPhoneBook : public testing::Test{
protected:
   
    PhoneBook* pb;
    
    void SetUp() override
    {
        
        std::stringstream s_str;
        s_str << "Bublik;Natalia;Nikolaevna;7;343;2887092;303;\n" << "Kuznecov;Petr;Ivanovich;9;12;45784638;-;\n" 
              << "Rybin;Dmitry;Valerievich;7;922;1235666;666;\n" << "Rybin;Ivan;Dmitrievich;7;900;2016667;-;\n";
        
        pb = new PhoneBook(s_str);
    }
    
   
    
    void TearDown() override
    {
        delete pb;
    }
    
};


TEST_F(TestPhoneBook, FoundOnce)
{
   std::string surname = "Bublik";
        
   auto answer = pb->GetPhoneNumber(surname);
   
    EXPECT_EQ(std::get<0>(answer), "");
}

TEST_F(TestPhoneBook, MoreThanOnce)
{
    std::string surname = "Rybin";

    auto answer = pb->GetPhoneNumber(surname);
    
    EXPECT_EQ(std::get<0>(answer), "found more than 1");
}

TEST_F(TestPhoneBook, NotFound)
{
    std::string surname = "Sidorov";

    auto answer = pb->GetPhoneNumber(surname);
    EXPECT_EQ(std::get<0>(answer), "not found");
}

TEST_F(TestPhoneBook, EmptyNotFound)
{
    std::string surname = "";

    auto answer = pb->GetPhoneNumber(surname);
    EXPECT_EQ(std::get<0>(answer), "not found");
}

TEST_F(TestPhoneBook, func_ChangePhoneNumber)
{
    std::string surname = "Bublik";

    ASSERT_EQ(std::get<0>(pb->GetPhoneNumber(surname)).empty(), true);

    PhoneNumber answer = std::get<1>(pb->GetPhoneNumber(surname))[0];
    EXPECT_EQ(answer.phoneNum, "2887092");

    pb->ChangePhoneNumber(Person{ "Bublik", "Natalia", "Nikolaevna" }, PhoneNumber{ 7, 343, "4567890", 303 });

    answer = std::get<1>(pb->GetPhoneNumber(surname))[0];
    EXPECT_EQ(answer.pageCode, 7);
    EXPECT_EQ(answer.cityCode, 343);
    EXPECT_EQ(answer.phoneNum, "4567890");
    EXPECT_EQ(answer.addNum, 303);
}

TEST_F(TestPhoneBook, func_SortByName)
{
    std::stringstream s_str;
    s_str << " Bublik Natalia Nikolaevna +7(343)2887092 303\n"
        << " Kuznecov Petr Ivanovich +9(12)45784638\n"
        << " Rybin Dmitry Valerievich +7(922)1235666 666\n"
        << " Rybin Ivan Dmitrievich +7(900)2016667\n";


    pb->SortByName();

    std::stringstream n_str;
    n_str << *pb;

    while (!n_str.eof())
    {
        std::string str_s;
        std::string str_n;

        s_str >> str_s;
        n_str >> str_n;

        EXPECT_EQ(str_n, str_s);
    }
}

TEST_F(TestPhoneBook, func_SortByPhone)
{
    std::stringstream s_str;
    s_str << " Bublik Natalia Nikolaevna +7(343)2887092 303\n"
          << " Rybin Ivan Dmitrievich +7(900)2016667\n"
          << " Rybin Dmitry Valerievich +7(922)1235666 666\n"
          << " Kuznecov Petr Ivanovich +9(12)45784638\n";

    pb->SortByPhone();

    std::stringstream n_str;
    n_str << *pb;

    while (!n_str.eof())
    {
        std::string str_s;
        std::string str_n;

        s_str >> str_s;
        n_str >> str_n;

        EXPECT_EQ(str_n, str_s);
    }
}