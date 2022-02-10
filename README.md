[![Build Status](https://ci.appveyor.com/api/projects/status/github/morinim/pocket_csv?svg=true)][appveyor]

## Overview

A minimal implementation of a CSV parser in C++17.

Low memory footprint and ease of use are the main concerns.

- Single-threaded. No additional worker threads.
- Lazy evaluated. Tokenization is not performed until the row is read.
- Single header file. Just include `"pocket_csv.h"`.
- *Automatic* delimiter guessing.
- Only standard C++17.

## Documentation

### Reading a file

```c++
std::istream is;

// ...

for (auto row : pocket_csv::parser(is))
{
  // do stuff with row here
}
```

## Setting up the build


## License

[Mozilla Public License v2.0][mpl2] (also available in the accompanying `LICENSE` file).

[appveyor]: https://ci.appveyor.com/project/morinim/vita
[mpl2]: https://www.mozilla.org/MPL/2.0/