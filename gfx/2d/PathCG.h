/* -*- Mode: C++; tab-width: 20; indent-tabs-mode: nil; c-basic-offset: 2 -*-
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
 * The Original Code is Mozilla Corporation code.
 *
 * The Initial Developer of the Original Code is Mozilla Foundation.
 * Portions created by the Initial Developer are Copyright (C) 2011
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Bas Schouten <bschouten@mozilla.com>
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

#ifndef MOZILLA_GFX_PATHCG_H_
#define MOZILLA_GFX_PATHCG_H_

#include <ApplicationServices/ApplicationServices.h>
#include "2D.h"

namespace mozilla {
namespace gfx {

class PathCG;

class PathBuilderCG : public PathBuilder
{
public:
  // absorbs a reference of aPath
  PathBuilderCG(CGMutablePathRef aPath, FillRule aFillRule)
    : mFigureActive(false)
    , mFillRule(aFillRule)
  {
      mCGPath = aPath;
  }

  PathBuilderCG(FillRule aFillRule)
    : mFigureActive(false)
    , mFillRule(aFillRule)
  {
      mCGPath = CGPathCreateMutable();
  }

  virtual ~PathBuilderCG();

  virtual void MoveTo(const Point &aPoint);
  virtual void LineTo(const Point &aPoint);
  virtual void BezierTo(const Point &aCP1,
                        const Point &aCP2,
                        const Point &aCP3);
  virtual void QuadraticBezierTo(const Point &aCP1,
                                 const Point &aCP2);
  virtual void Close();
  virtual void Arc(const Point &aOrigin, Float aRadius, Float aStartAngle,
                   Float aEndAngle, bool aAntiClockwise = false);
  virtual Point CurrentPoint() const;

  virtual TemporaryRef<Path> Finish();

private:
  friend class PathCG;

  void EnsureActive(const Point &aPoint);

  CGMutablePathRef mCGPath;
  bool mFigureActive;
  Point mCurrentPoint;
  Point mBeginPoint;
  FillRule mFillRule;
};

class PathCG : public Path
{
public:
  PathCG(CGMutablePathRef aPath, FillRule aFillRule)
    : mPath(aPath)
    , mFillRule(aFillRule)
  {
    CGPathRetain(mPath);
  }
  virtual ~PathCG() { CGPathRelease(mPath); }

  virtual BackendType GetBackendType() const { return BACKEND_COREGRAPHICS; }

  virtual TemporaryRef<PathBuilder> CopyToBuilder(FillRule aFillRule = FILL_WINDING) const;
  virtual TemporaryRef<PathBuilder> TransformedCopyToBuilder(const Matrix &aTransform,
                                                             FillRule aFillRule = FILL_WINDING) const;

  virtual bool ContainsPoint(const Point &aPoint, const Matrix &aTransform) const;
  virtual Rect GetBounds(const Matrix &aTransform = Matrix()) const;
  virtual Rect GetStrokedBounds(const StrokeOptions &aStrokeOptions,
                                const Matrix &aTransform = Matrix()) const;

  virtual FillRule GetFillRule() const { return mFillRule; }

  CGMutablePathRef GetPath() const { return mPath; }

private:
  friend class DrawTargetCG;

  CGMutablePathRef mPath;
  bool mEndedActive;
  Point mEndPoint;
  FillRule mFillRule;
};

}
}

#endif
