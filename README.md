![C++17](https://img.shields.io/badge/c%2B%2B-17-blue.svg)
[![License](https://img.shields.io/badge/license-MPLv2-blue.svg)][mpl2]

## Overview

A minimal implementation of a CSV parser in C++17.

Low memory footprint and ease of use are the main concerns.

- Single-threaded. No additional worker threads.
- Lazy evaluated. Tokenization is not performed until the row is read.
- Single header file. Just include `"pocket_csv.h"`.
- *Automatic* dialect guessing (delimiter, header...).
- Only standard C++17.

## Documentation

### Reading a file

```c++
std::istream is;
// ...

for (auto row : pocket_csv::parser(is))
  for (auto cell : row)
  {
    // do stuff with cells here
  }
```

### Specifying the CSV format

The parser has a decent guessing mechanism but, in some cases, it's preferrable to specify the exact parameters of the CSV file.

```c++
std::istream is;
// ...

pocket_csv::dialect dialect;
dialect.delimiter = '|';
dialect.quote = '*';

for (auto row : pocket_csv::parser(is, dialect))
{
  // do stuff with rows here
}

```

### Filtering rows

```c++
auto filter = [](const auto &row) { return row.front() != ""; };

std::istringstream is;
// ...

for (auto row : pocket_csv::parser(is).filter_hook(filter))
{
  // do stuff with rows having a not empty first element
}
```

## License

[Mozilla Public License v2.0][mpl2] (also available in the accompanying `LICENSE` file).


[mpl2]: https://www.mozilla.org/MPL/2.0/