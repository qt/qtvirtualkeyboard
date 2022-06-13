#!/usr/bin/env python
# Copyright (C) 2021 The Qt Company Ltd.
# SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

import os
import sys
import zipfile
import tempfile
import shutil
import fnmatch

#
# This utility script unpacks the Cerence SDK to appropriate directory
# structure for Qt Virtual Keyboard.
#
# Usage: unpack.py <filename.zip> [<target dir>]
#
# - <filename.zip>          The Cerence SDK zip.
# - <target dir>            Target directory to unpack files to. The
#                           directory can be located out of tree.
#                           The default directory is src/plugins/cerence/sdk.
#
# The script will overwrite existing files, so be careful.
#

#
# Unpack rule list
#
# Each list entry is a dictionary consisting of target directory as
# key and matching pattern as value. The dictionary can be defined in
# the following ways:
#
# Note: The rules within the dictionary are executed in arbitrary order.
#       Add a new list entry if the order is significant.
#
# Format:
#   1. { 'target dir 1': [ 'pattern1', 'pattern2', ... ], 'target dir 2': ... }
#       - Each pattern is matched against the zip file contents. The file is
#         copied to target dir if the pattern matches. Each pattern is handled
#         independent of each other.
#
#   2. { 'target dir 1': [ [ 'file group pattern', 'sub pattern1', ... ] ], 'target dir 2': ... }
#       - First the file group pattern is matched against the zip file contents.
#         Then all the sub patterns are matched in the sub directory specified by
#         the first match. If all the sub patterns match, then first match from
#         file group pattern and all the matching files from sub pattterns are copied.
#         The purpose of this option is to copy coupled files, e.g. DLL and LIB
#         files found in the same directory.
#

T9WRITE_DIR = 't9write/'
T9WRITE_DATA_DIR = 't9write/data/'
XT9_DIR = 'xt9/'
XT9_DATA_DIR = 'xt9/data/'

UNPACK_RULES = [

##############################################################################
#
#   T9 Write
#
##############################################################################

{ # Header files
T9WRITE_DIR + 'api': [
    '*/decuma_hwr.h',
    '*/decuma_hwr_cjk.h',
    '*/decuma_hwr_types.h',
    '*/decuma_point.h',
    '*/decumaBasicTypes.h',
    '*/decumaBasicTypesMinMax.h',
    '*/decumaCharacterSetType.h',
    '*/decumaCurve.h',
    '*/decumaFunctionalSupport.h',
    '*/decumaFunctionalSupportCheck.h',
    '*/decumaLanguages.h',
    '*/decumaLiteFunctionalSupport.h',
    '*/decumaPlusFunctionalSupport.h',
    '*/decumaRuntimeMallocData.h',
    '*/decumaStatus.h',
    '*/decumaStorageSpecifiers.h',
    '*/decumaSymbolCategories.h',
    '*/decumaUnicodeTypes.h',
    '*/cerence_handwriting_alpha_version.h',
    '*/cerence_handwriting_api_version.h',
    '*/cerence_handwriting_cjk_version.h',
    '*/xxchApiOem.h',
    '*/xxchOem.h',
],
}, { # Data
T9WRITE_DATA_DIR + 'arabic': [
    '*/Arabic/*_le.bin',
],
T9WRITE_DATA_DIR + 'hebrew': [
    '*/Hebrew/*_le.bin',
],
T9WRITE_DATA_DIR + 'thai': [
    '*/*Thai*/*_le.bin',
],
T9WRITE_DATA_DIR + '': [
    '*/*_le.bin',
    '*/*.hdb',
    '*/*.phd',
],
}, { # Libraries
# T9 Write ARM Linux 32-bit
T9WRITE_DIR + 'lib/linux/arm/static/alphabetic': [
    '*T9Write_Alphabetic*/arm_linux*_32bit/*.a',
    '*T9Write_Alphabetic*/arm_linux*_32bit/*.o',
],
T9WRITE_DIR + 'lib/linux/arm/shared/alphabetic': [
    '*T9Write_Alphabetic*/arm_linux*_32bit/*.so',
],
T9WRITE_DIR + 'lib/linux/arm/static/cjk': [
    '*T9Write_CJK*/arm_linux*_32bit/*.a',
    '*T9Write_CJK*/arm_linux*_32bit/*.o',
],
T9WRITE_DIR + 'lib/linux/arm/shared/cjk': [
    '*T9Write_CJK*/arm_linux*_32bit/*.so',
],
# T9 Write ARM Linux 64-bit
T9WRITE_DIR + 'lib/linux/arm64/static/alphabetic': [
    '*T9Write_Alphabetic*/arm_linux*_64bit/*.a',
    '*T9Write_Alphabetic*/arm_linux*_64bit/*.o',
],
T9WRITE_DIR + 'lib/linux/arm64/shared/alphabetic': [
    '*T9Write_Alphabetic*/arm_linux*_64bit/*.so',
],
T9WRITE_DIR + 'lib/linux/arm64/static/cjk': [
    '*T9Write_CJK*/arm_linux*_64bit/*.a',
    '*T9Write_CJK*/arm_linux*_64bit/*.o',
],
T9WRITE_DIR + 'lib/linux/arm64/shared/cjk': [
    '*T9Write_CJK*/arm_linux*_64bit/*.so',
],
# T9 Write x86 Linux 32-bit
T9WRITE_DIR + 'lib/linux/x86/static/alphabetic': [
    '*T9Write_Alphabetic*/i86_linux*_32bit/*.a',
    '*T9Write_Alphabetic*/i86_linux*_32bit/*.o',
],
T9WRITE_DIR + 'lib/linux/x86/shared/alphabetic': [
    '*T9Write_Alphabetic*/i86_linux*_32bit/*.so',
],
T9WRITE_DIR + 'lib/linux/x86/static/cjk': [
    '*T9Write_CJK*/i86_linux*_32bit/*.a',
    '*T9Write_CJK*/i86_linux*_32bit/*.o',
],
T9WRITE_DIR + 'lib/linux/x86/shared/cjk': [
    '*T9Write_CJK*/i86_linux*_32bit/*.so',
],
# T9 Write x86 Linux 64-bit
T9WRITE_DIR + 'lib/linux/x86_64/static/alphabetic': [
    '*T9Write_Alphabetic*/i86_linux*_64bit/*.a',
    '*T9Write_Alphabetic*/i86_linux*_64bit/*.o',
],
T9WRITE_DIR + 'lib/linux/x86_64/shared/alphabetic': [
    '*T9Write_Alphabetic*/i86_linux*_64bit/*.so',
],
T9WRITE_DIR + 'lib/linux/x86_64/static/cjk': [
    '*T9Write_CJK*/i86_linux*_64bit/*.a',
    '*T9Write_CJK*/i86_linux*_64bit/*.o',
],
T9WRITE_DIR + 'lib/linux/x86_64/shared/cjk': [
    '*T9Write_CJK*/i86_linux*_64bit/*.so',
],
# T9 Write x86 Win32 32-bit
T9WRITE_DIR + 'lib/win32/x86/static/alphabetic': [
    '*T9Write_Alphabetic*/i86_win32_32bit/libt9write*.lib',
],
T9WRITE_DIR + 'lib/win32/x86/shared/alphabetic': [
    [ '*T9Write_Alphabetic*/i86_win32_32bit/t9write*.dll', 't9write*.lib' ],
],
T9WRITE_DIR + 'lib/win32/x86/static/cjk': [
    '*T9Write_CJK*/i86_win32_32bit/libt9write*.lib',
],
T9WRITE_DIR + 'lib/win32/x86/shared/cjk': [
    [ '*T9Write_CJK*/i86_win32_32bit/t9write*.dll', 't9write*.lib' ],
],
# T9 Write x86 Win32 64-bit
T9WRITE_DIR + 'lib/win32/amd64/static/alphabetic': [
    '*T9Write_Alphabetic*/i86_win32_64bit/libt9write*.lib',
],
T9WRITE_DIR + 'lib/win32/amd64/shared/alphabetic': [
    [ '*T9Write_Alphabetic*/i86_win32_64bit/t9write*.dll', 't9write*.lib' ],
],
T9WRITE_DIR + 'lib/win32/amd64/static/cjk': [
    '*T9Write_CJK*/i86_win32_64bit/libt9write*.lib',
],
T9WRITE_DIR + 'lib/win32/amd64/shared/cjk': [
    [ '*T9Write_CJK*/i86_win32_64bit/t9write*.dll', 't9write*.lib' ],
],
},

##############################################################################
#
#   XT9
#
##############################################################################

{ # Header files
XT9_DIR + 'api': [
    '*/et9api.h',
    '*/et9awapi.h',
    '*/et9cpapi.h',
    '*/et9kapi.h',
    '*/et9kbdef.h',
    '*/et9navapi.h',
    '*/xxet9oem.h',
],
}, { # Libraries
# XT9 ARM Linux 32-bit
XT9_DIR + 'lib/linux/arm/static': [
    '*/Xt9/*/arm_linux*_32bit/*.a',
    '*/Xt9/*/arm_linux*_32bit/*.o',
],
XT9_DIR + 'lib/linux/arm/shared': [
    '*/Xt9/*/arm_linux*_32bit/*.so',
],
# XT9 ARM Linux 64-bit
XT9_DIR + 'lib/linux/arm64/static': [
    '*/Xt9/*/arm_linux*_64bit/*.a',
    '*/Xt9/*/arm_linux*_64bit/*.o',
],
XT9_DIR + 'lib/linux/arm64/shared': [
    '*/Xt9/*/arm_linux*_64bit/*.so',
],
# XT9 x86 Linux 32-bit
XT9_DIR + 'lib/linux/x86/static': [
    '*/Xt9/*/i86_linux*_32bit/*.a',
    '*/Xt9/*/i86_linux*_32bit/*.o',
],
XT9_DIR + 'lib/linux/x86/shared': [
    '*/Xt9/*/i86_linux*_32bit/*.so',
],
# XT9 x86 Linux 64-bit
XT9_DIR + 'lib/linux/x86_64/static': [
    '*/Xt9/*/i86_linux*_64bit/*.a',
    '*/Xt9/*/i86_linux*_64bit/*.o',
],
XT9_DIR + 'lib/linux/x86_64/shared': [
    '*/Xt9/*/i86_linux*_64bit/*.so',
],
# XT9 x86 Win32 32-bit
XT9_DIR + 'lib/win32/x86/static': [
    '*/Xt9/*/i86_win32_32bit/libxt9*.lib',
],
XT9_DIR + 'lib/win32/x86/shared': [
    [ '*/Xt9/*/i86_win32_32bit/xt9*.dll', 'xt9*.lib' ],
],
# XT9 x86 Win32 64-bit
XT9_DIR + 'lib/win32/amd64/static': [
    '*/Xt9/*/i86_win32_64bit/libxt9*.lib',
],
XT9_DIR + 'lib/win32/amd64/shared': [
    [ '*/Xt9/*/i86_win32_64bit/xt9*.dll', 'xt9*.lib' ],
],
},

##############################################################################
#
#   XT9 Data
#
##############################################################################

{
XT9_DATA_DIR: [
    '*/*.ldb',
],
},

]

#
# Blacklist
#
# File matching rules for blacklisted items. Matched before UNPACK_RULES.
#

BLACKLIST_RULES = [
'*__MACOSX*',
'*/.DS_Store',
]

def blacklist(file_list):
    result = []
    for file_name in file_list:
        match = False
        for blacklist_rule in BLACKLIST_RULES:
            match = fnmatch.fnmatch(file_name, blacklist_rule)
            if match:
                break
        if not match:
            result.append(file_name)
    return result

def unzip(zip_file, target_dir):
    zip_list = []
    if os.path.isdir(zip_file):
        base_dir, sdk_dir = os.path.split(zip_file.replace('\\', '/').rstrip('/'))
        base_dir_length = len(base_dir) + 1 if base_dir else 0
        if not 'T9Write' in sdk_dir:
            print("Error: The input directory name '" + sdk_dir + "' does not contain 'T9Write'.")
            print("Please unzip the file to a directory named after the zip file and try again.")
            return zip_list
        for root, dirs, files in os.walk(zip_file):
            for file_name in files:
                sub_dir = root[base_dir_length:]
                dst_dir = os.path.join(target_dir, sub_dir)
                if not os.path.exists(dst_dir):
                    os.makedirs(dst_dir)
                shutil.copy2(os.path.join(root, file_name), dst_dir)
                os.chmod(os.path.join(dst_dir, file_name), 0o644)
                zip_list.append(os.path.join(sub_dir, file_name).replace('\\', '/'))
        return zip_list
    with zipfile.ZipFile(zip_file, 'r') as z:
        zip_list = sorted(blacklist(z.namelist()))
        zip_basename = os.path.splitext(os.path.basename(zip_file))[0]
        if zip_list and zip_basename in zip_list[0]:
            zip_basename = ''
        zip_list = [os.path.join(zip_basename, zip_name).replace('\\', '/') for zip_name in zip_list]
        z.extractall(os.path.join(target_dir, zip_basename))
    return zip_list

def match_file_list(file_list, base_dir, fnpattern):
    result_list = [file_name for file_name in file_list \
        if fnmatch.fnmatch(file_name, fnpattern) and \
            os.path.isfile(os.path.join(base_dir, file_name))]
    for file_name in result_list:
        file_list.remove(file_name)
    return result_list

def unpack(zip_list, zip_dir, out_dir):
    if not zip_list:
        return
    for unpack_rules in UNPACK_RULES:
        process_unpack_rules(zip_list, zip_dir, out_dir, unpack_rules)

def process_unpack_rules(zip_list, zip_dir, out_dir, unpack_rules):
    for (target_dir, match_rules) in unpack_rules.items():
        for match_rule in match_rules:
            # Match
            match_rule_group = match_rule if isinstance(match_rule, list) else [match_rule]
            match_group_candidates = [match_file_list(zip_list, zip_dir, match_rule_group[0])]
            if len(match_rule_group) > 1:
                while len(match_group_candidates[0]) > 0:
                    match_group0_candidate = match_group_candidates[0][0]
                    all_sub_groups_match = True
                    for sub_group_rule in match_rule_group[1:]:
                        fnpattern = os.path.join(os.path.dirname(match_group0_candidate), sub_group_rule).replace('\\', '/')
                        sub_group_candidates = match_file_list(zip_list, zip_dir, fnpattern)
                        if not sub_group_candidates:
                            all_sub_groups_match = False
                            break
                        match_group_candidates.append(sub_group_candidates)
                    if all_sub_groups_match:
                        match_group_candidates[0] = [match_group0_candidate]
                        break
                    else:
                        match_group_candidates = [match_group_candidates[0][1:]]

            # Copy
            if match_group_candidates:
                for match_group_candidate in match_group_candidates:
                    for zip_name in match_group_candidate:
                        dst_dir = os.path.join(out_dir, target_dir)
                        if not os.path.exists(dst_dir):
                            os.makedirs(dst_dir)
                        src = os.path.join(zip_dir, zip_name).replace('\\', '/')
                        dst = os.path.join(dst_dir, os.path.basename(zip_name)).replace('\\', '/')
                        print(zip_name + ' -> ' + dst)
                        shutil.copy2(src, dst)

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("Usage: %s <filename.zip> [<target dir>]" % os.path.basename(__file__))
        exit()

    out_dir = os.path.join(sys.path[0], 'sdk') if len(sys.argv) == 2 else sys.argv[2]
    zip_dir = tempfile.mkdtemp()

    try:
        unpack(unzip(sys.argv[1], zip_dir), zip_dir, out_dir)
    except Exception as e:
        print(e)
    finally:
        shutil.rmtree(zip_dir)
