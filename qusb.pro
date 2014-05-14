TEMPLATE = subdirs

SUBDIRS = src

CONFIG(demo) {
    SUBDIRS += demo
    demo.depends = src
}
