# Description

Cloud Files Linux Style Utilities and Libraries.

Standard Linux file utilities for cloud files interaction.  These utilties
behave similarly to their Linux counterparts (i.e. cfls ← ls).  Also included
with these utilities is a cf-bindings library that provides C bindings for cloud
files.  For these utilities there is a façade as well that can be used but isn't
required.

# Installation

This package should be available from most package managers and installable as
`cf-utils`.  If not, a source installation can be done (from the source
directory):

```
mkdir build && cd build
cmake ..
make install
```

The current status of the build—if you're using master as your source
directory—is:

[![Build Status](https://secure.travis-ci.org/alunduil/cf-utils.png?branch=master)](https://travis-ci.org/alunduil/cf-utils)

# Usage

* Accounts
* Authentication
* Permissions
* Containers
* Objects
* Operations
* CDN-Enabled Containers

# Authors

* Alex Brandt <alunduil@alunduil.com>

# Known Issues

Known issues can be found in the github issue list at
https://github.com/alunduil/cf-utils/issues.

# Troubleshooting

If you need to troubleshoot an issue or submit information in a bug report, we
recommend ensuring the build has debugging enabled and any stacktraces are
included.
