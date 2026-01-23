/**
 *  \file
 *  \remark This file is part of POCKET_CSV.
 *
 *  \copyright Copyright (C) 2022 EOS di Manlio Morini.
 *
 *  \license
 *  This Source Code Form is subject to the terms of the Mozilla Public
 *  License, v. 2.0. If a copy of the MPL was not distributed with this file,
 *  You can obtain one at http://mozilla.org/MPL/2.0/
 */

#include "../pocket_csv.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

struct dataset_info
{
  pocket_csv::dialect::header_e has_header;
  std::size_t rows;
  std::size_t cols;
};

const std::string s_abalone_nh(R"(
M,0.455,0.365,0.095,0.514,0.2245,0.101,0.15,15
M,0.35,0.265,0.09,0.2255,0.0995,0.0485,0.07,7
F,0.53,0.42,0.135,0.677,0.2565,0.1415,0.21,9
M,0.44,0.365,0.125,0.516,0.2155,0.114,0.155,10
I,0.33,0.255,0.08,0.205,0.0895,0.0395,0.055,7
I,0.425,0.3,0.095,0.3515,0.141,0.0775,0.12,8
F,0.53,0.415,0.15,0.7775,0.237,0.1415,0.33,20
F,0.545,0.425,0.125,0.768,0.294,0.1495,0.26,16
M,0.475,0.37,0.125,0.5095,0.2165,0.1125,0.165,9
F,0.55,0.44,0.15,0.8945,0.3145,0.151,0.32,19)");

const std::string s_abalone_h(R"(
sex,length,diameter,height,whole weight,shucked weight,viscera weight,shell weight,rings
)" + s_abalone_nh);

const std::string s_iris_nh(R"(
5.1,3.5,1.4,0.2,Iris-setosa
4.9,3,1.4,0.2,Iris-setosa
4.7,3.2,1.3,0.2,Iris-setosa
7,3.2,4.7,1.4,Iris-versicolor
6.4,3.2,4.5,1.5,Iris-versicolor
6.9,3.1,4.9,1.5,Iris-versicolor
6.3,2.5,5,1.9,Iris-virginica
6.5,3,5.2,2,Iris-virginica
6.2,3.4,5.4,2.3,Iris-virginica
5.9,3,5.1,1.8,Iris-virginica)");

const std::string s_iris_h(R"(
sepal length,sepal width,petal length,petal width,class
)" + s_iris_nh);

const std::string s_car_speed_nh(R"(
Blue,32,NewMexico
Red,45,Arizona
Blue,-9999,Colorado
White,34,Arizona
Red,25,Arizona
Blue,34,NewMexico
Black,,Colorado
White,31,Arizona
Red,26,Colorado
White,31,Arizona)");

const std::string s_car_speed_h(R"(
Color,Speed,State
)" + s_car_speed_nh);

const std::string s_colors_nh(R"(
Blue
Red
Blue
White
Red
Blue
Black
White
Red
White)");

const std::string s_colors_h(R"(
COLOR
)" + s_colors_nh);

const std::string s_addresses(R"(
John,Doe,120 jefferson st.,Riverside, NJ, 08075
Jack,McGinnis,220 hobo Av.,Phila, PA,09119
"John ""Da Man""",Repici,120 Jefferson St.,Riverside, NJ,08075
Stephen,Tyler,"7452 Terrace ""At the Plaza"" road",SomeTown,SD, 91234
,Blankman,,SomeTown, SD, 00298
"Joan ""the bone"", Anne",Jet,"9th, at Terrace plc",Desert City,CO,00123)");

const std::string s_air_travel(R"(
"Month", "1958", "1959", "1960"
"JAN",  340,  360,  417
"FEB",  318,  342,  391
"MAR",  362,  406,  419
"APR",  348,  396,  461
"MAY",  363,  420,  472
"JUN",  435,  472,  535
"JUL",  491,  548,  622
"AUG",  505,  559,  606
"SEP",  404,  463,  508
"OCT",  359,  407,  461
"NOV",  310,  362,  390
"DEC",  337,  405,  432)");

const std::string s_numbers_nh(R"(
123.11
234.22
345.33
456.44
567.55)");

const std::string s_numbers_h(R"(
VALUE
)" + s_numbers_nh);

const std::vector<std::pair<std::string, dataset_info>> datasets_with_info =
{
  {s_abalone_h, {pocket_csv::dialect::HAS_HEADER, 11u, 9u}},
  {s_abalone_nh, {pocket_csv::dialect::NO_HEADER, 10u, 9u}},
  {s_iris_h, {pocket_csv::dialect::HAS_HEADER, 11u, 5u}},
  {s_iris_nh, {pocket_csv::dialect::NO_HEADER, 10u, 5u}},
  {s_car_speed_h, {pocket_csv::dialect::HAS_HEADER, 11u, 3u}},
  {s_car_speed_nh, {pocket_csv::dialect::NO_HEADER, 10u, 3u}},
  {s_addresses, {pocket_csv::dialect::NO_HEADER, 6u, 6u}},
  {s_air_travel, {pocket_csv::dialect::HAS_HEADER, 13u, 4u}},
  {s_colors_h, {pocket_csv::dialect::HAS_HEADER, 11u, 1u}},
  {s_colors_nh, {pocket_csv::dialect::NO_HEADER, 10u, 1u}},
  {s_numbers_h, {pocket_csv::dialect::HAS_HEADER, 6u, 1u}},
  {s_numbers_nh, {pocket_csv::dialect::NO_HEADER, 5u, 1u}}
};

TEST_SUITE("POCKET_CSV")
{

TEST_CASE("Reading")
{
  for (auto [ds, info] : datasets_with_info)
  {
    std::istringstream is(ds);

    for (auto record : pocket_csv::parser(is))
    {
      const auto cols(info.cols);
      CHECK(record.size() == cols);
    }

    pocket_csv::parser parser(is);
    const auto cells(info.rows);
    const auto dist(std::distance(parser.begin(), parser.end()));
    CHECK(dist == cells);
  }
}

TEST_CASE("Checking specific values")
{
  using row = pocket_csv::parser::record_t;

  // --------------------------------------------------------------
  const pocket_csv::parser::record_t row1_abalone =
    {"M", "0.455", "0.365", "0.095", "0.514", "0.2245", "0.101", "0.15", "15"};

  std::istringstream abalone(s_abalone_h);
  pocket_csv::parser csv_abalone(abalone);
  csv_abalone.trim_ws(true);

  SUBCASE("Abalone")
  {
    auto header_abalone(*csv_abalone.begin());
    CHECK(header_abalone.size() == 9);
    CHECK(
      header_abalone
      == row{"sex", "length", "diameter", "height", "whole weight",
             "shucked weight", "viscera weight", "shell weight", "rings"});

    const auto row1(*std::next(csv_abalone.begin()));
    CHECK(row1.size() == 9);
    CHECK(row1 == row1_abalone);
  }

  SUBCASE("Abalone skip header")
  {
    csv_abalone.skip_header();

    const auto row1(*csv_abalone.begin());
    CHECK(row1.size() == 9);
    CHECK(row1 == row1_abalone);
  }

  // --------------------------------------------------------------
  const pocket_csv::parser::record_t row1_iris =
    {"5.1", "3.5", "1.4", "0.2", "Iris-setosa"};

  std::istringstream iris(s_iris_h);
  pocket_csv::parser csv_iris(iris);
  csv_iris.trim_ws(true);

  SUBCASE("Iris")
  {
    const auto header_iris(*csv_iris.begin());
    CHECK(header_iris.size() == 5);
    CHECK(
      header_iris
      == row{"sepal length", "sepal width", "petal length", "petal width",
             "class"});

    const auto row1(*std::next(csv_iris.begin()));
    CHECK(row1.size() == 5);
    CHECK(row1 == row1_iris);
  }

  SUBCASE("Iris skip header")
  {
    csv_iris.skip_header();

    const auto row1(*csv_iris.begin());
    CHECK(row1.size() == 5);
    CHECK(row1 == row1_iris);
  }

  // --------------------------------------------------------------
  const pocket_csv::parser::record_t row1_car_speed =
    {"Blue", "32", "NewMexico"};

  std::istringstream car_speed(s_car_speed_h);
  pocket_csv::parser csv_car_speed(car_speed);

  SUBCASE("Car speed")
  {
    const auto header_car_speed(*csv_car_speed.begin());
    CHECK(header_car_speed.size() == 3);
    CHECK(header_car_speed == row{"Color", "Speed", "State"});

    const auto row1(*std::next(csv_car_speed.begin()));
    CHECK(row1.size() == 3);
    CHECK(row1 == row1_car_speed);
  }

  SUBCASE("Car speed skip header")
  {
    csv_car_speed.skip_header();

    const auto row1(*csv_car_speed.begin());
    CHECK(row1.size() == 3);
    CHECK(row1 == row1_car_speed);
  }

  // --------------------------------------------------------------
  std::istringstream colors(s_colors_h);
  pocket_csv::parser csv_colors(colors);

  auto header_colors(csv_colors.begin());
  CHECK(header_colors->size() == 1);
  CHECK(header_colors->front() == "COLOR");

  auto row1_colors(std::next(header_colors));
  CHECK(row1_colors->size() == 1);
  CHECK(row1_colors->front() == "Blue");

  auto row2_colors(std::next(row1_colors));
  CHECK(row2_colors->size() == 1);
  CHECK(row2_colors->front() == "Red");

  // --------------------------------------------------------------
  const pocket_csv::parser::record_t row1_address =
    {"John", "Doe", "120 jefferson st.", "Riverside", " NJ", " 08075"};
  const pocket_csv::parser::record_t row2_address =
    {"Jack", "McGinnis", "220 hobo Av.", "Phila", " PA", "09119"};

  std::istringstream addresses(s_addresses);
  pocket_csv::parser csv_addresses(addresses);

  SUBCASE("Addresses")
  {
    const auto row1(*csv_addresses.begin());
    CHECK(row1.size() == 6);
    CHECK(row1 == row1_address);

    const auto row2(*std::next(csv_addresses.begin()));
    CHECK(row2.size() == 6);
    CHECK(row2 == row2_address);
  }

  SUBCASE("Addresses skip header")
  {
    csv_addresses.skip_header();

    const auto row1(*csv_addresses.begin());
    CHECK(row1.size() == 6);
    CHECK(row1 == row1_address);

    const auto row2(*std::next(csv_addresses.begin()));
    CHECK(row2.size() == 6);
    CHECK(row2 == row2_address);
  }

  // --------------------------------------------------------------
  const pocket_csv::parser::record_t row1_air_travel =
    {"JAN", "340", "360", "417"};

  std::istringstream air_travel(s_air_travel);
  pocket_csv::parser csv_air_travel(air_travel);
  csv_air_travel.trim_ws(true);

  SUBCASE("Air travel")
  {
    const auto header_air_travel(*csv_air_travel.begin());
    CHECK(header_air_travel.size() == 4);
    CHECK(header_air_travel == row{"Month", "1958", "1959", "1960"});

    const auto row1(*std::next(csv_air_travel.begin()));
    CHECK(row1.size() == 4);
    CHECK(row1 == row1_air_travel);
  }

  SUBCASE("Air travel skip header")
  {
    csv_air_travel.skip_header();

    const auto row1(*csv_air_travel.begin());
    CHECK(row1.size() == 4);
    CHECK(row1 == row1_air_travel);
  }
}

TEST_CASE("Sniffer")
{
  using namespace pocket_csv;

  const std::vector delimiters = {',', ';', ':', '\t'};

  const auto controlla([](const std::string &s, dialect::header_e h, char d)
                       {
                         std::istringstream is(s);
                         pocket_csv::parser csvp(is);

                         CHECK(csvp.active_dialect().has_header == h);
                         CHECK(csvp.active_dialect().delimiter == d);
                       });

  for (auto [ds, info] : datasets_with_info)
    if (info.cols > 1)
      for (auto c : delimiters)
      {
        std::string s;
        if (c == ',')
          s = ds;
        else
          std::replace_copy(ds.begin(), ds.end(), std::back_inserter(s),
                            ',', c);

        controlla(s, info.has_header, c);
      }
    else
      controlla(ds, info.has_header, '\0');
}

TEST_CASE("Filtering")
{
  const auto filter([](const auto &row)
                    {
                      return row.back() == "Iris-setosa";
                    });

  std::istringstream is(s_iris_nh);

  for (auto record : pocket_csv::parser(is).filter_hook(filter))
    CHECK(record.back() == "Iris-setosa");
}

TEST_CASE("Head")
{
  SUBCASE("Empty dataset")
  {
    std::istringstream empty;
    const auto head(pocket_csv::head(empty, {}, 1000));

    CHECK(head.size() == 1);
    CHECK(head.front().empty());
  }

  SUBCASE("Cardinality")
  {
    for (const auto &[ds, info] : datasets_with_info)
    {
      std::istringstream is(ds);

      const auto dialect(pocket_csv::sniffer(is));
      for (std::size_t n(0); n <= info.rows; ++n)
      {
        const auto head(pocket_csv::head(is, dialect, n));

        if (info.has_header && n >= info.rows)
          CHECK(head.size() == info.rows);
        else
          CHECK(head.size() == n + 1);

        CHECK(head.front().size() == info.cols);
      }
    }
  }
}

}  // TEST_SUITE("POCKET_CSV")
