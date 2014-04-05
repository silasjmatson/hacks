# Concurrency!

A [Lattice][lattice] application created by a brave individual! Rails may be a
more conservative choice, but clearly it pissed off the brave individual behind
this app, and so here we are.

You may want to tweak this README to add more specific documentation about this
app. Or you don't have to, whatever. But perhaps you want to know more about
using Lattice, so here we go:

## Documentation

[Please see the Lattice Wiki][wiki] for detailed documentation and usage notes.

[YARD Documentation][yardoc] is also available.

[wiki]: https://github.com/celluloid/lattice/wiki
[yardoc]: http://rubydoc.info/github/celluloid/lattice/master/frames

## Adding Resources

Resources are the heart of any Lattice application. They represent "RESTful"
HTTP endpoints that respond in a fully deterministic manner depending on their
state.

Unfortunately, there's no resource generator at present! You will need to view
the [Lattice Wiki documentation on Resources][resources] to find out information
about the Resource API and how to add new resources to your application.

[resources]: https://github.com/celluloid/lattice/wiki/Resources

## Starting the app

To launch the application, run:

```
$ lattice server
```

By default the appliaction will launch on http://127.0.0.1:3000/

