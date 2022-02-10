[![Build Status](https://ci.appveyor.com/api/projects/status/github/morinim/pocket_csv?svg=true)][appveyor]

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
{
  // do stuff with rows here
}
```

### Specifying the CSV Format

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

## License

[Mozilla Public License v2.0][mpl2] (also available in the accompanying `LICENSE` file).

[appveyor]: https://ci.appveyor.com/project/morinim/vita
[mpl2]: https://www.mozilla.org/MPL/2.0/