/* -*- Mode: c++; c-basic-offset: 4; tab-width: 20; indent-tabs-mode: nil; -*-
 * ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is Mozilla Android code.
 *
 * The Initial Developer of the Original Code is Mozilla Foundation.
 * Portions created by the Initial Developer are Copyright (C) 2010
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Brad Lassey <blassey@mozilla.com>
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#ifndef NSFILEPICKER_H
#define NSFILEPICKER_H

#include "nsBaseFilePicker.h"
#include "nsString.h"

class nsFilePicker : public nsBaseFilePicker
{
public:
    NS_DECL_ISUPPORTS

    NS_IMETHODIMP Init(nsIDOMWindow *parent, const nsAString& title,
                       PRInt16 mode);
    NS_IMETHOD AppendFilter(const nsAString & aTitle,
                            const nsAString & aFilter);
    NS_IMETHOD GetDefaultString(nsAString & aDefaultString);
    NS_IMETHOD SetDefaultString(const nsAString & aDefaultString);
    NS_IMETHOD GetDefaultExtension(nsAString & aDefaultExtension);
    NS_IMETHOD SetDefaultExtension(const nsAString & aDefaultExtension);
    NS_IMETHOD GetFile(nsILocalFile * *aFile);
    NS_IMETHOD GetFileURL(nsIURI * *aFileURL);
    NS_IMETHOD SetDisplayDirectory(nsILocalFile *aDisplayDirectory);
    NS_IMETHOD GetDisplayDirectory(nsILocalFile **aDisplayDirectory);
    NS_IMETHOD Show(PRInt16 *aReturn);
private:
    void InitNative(nsIWidget*, const nsAString&, PRInt16) {};
    nsString mFilePath;
    nsString mFilters;
};
#endif
