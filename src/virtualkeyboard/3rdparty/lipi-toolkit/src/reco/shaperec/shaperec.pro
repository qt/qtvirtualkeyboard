TEMPLATE = subdirs

SUBDIRS += \
    common \
    featureextractor \
    activedtw \
    neuralnet \
    nn \
    preprocessing

activedtw.depends = sub-common sub-featureextractor
neuralnet.depends = sub-common sub-featureextractor
nn.depends = sub-common sub-featureextractor
preprocessing.depends = sub-common
