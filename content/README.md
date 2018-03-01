This is an example for the discussion on CCN-lite issue [#207](https://github.com/cn-uofbasel/ccn-lite/issues/207).

## Install
1. Clone the repository into your ``${RIOTBASE}/examples/`` directory.
2. Compile the code with  (replace ``pba-d-01-kw2x`` with the acutal RIOT supported board you are going to use)
```bash
$ BOARD="pba-d-01-kw2x" make
```
3. Flash it to your target via
```bash
$ BOARD="pba-d-01-kw2x" make flash
```

## Usage
In your RIOT shell, start CCN-lite by
```bash
# ccnl_open 3
```
(replace 3 with the actual interface id of your network interface) and create an interest via
```bash
# ccnl_int /foo/bar
```
