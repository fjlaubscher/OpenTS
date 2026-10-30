/*******************************************************************************
 *                                O P E N  T S
 *******************************************************************************
 * SPDX-License-Identifier: GPL-3.0-or-later
 * Copyright 2026 OpenTS contributors
 *
 * See LICENSE.md for applicable additional terms and warranty disclaimers.
 ******************************************************************************/


#pragma once

#include "rect.h"


void Now_Playing_Set_View(Rect const & area);
void Now_Playing_AI(void);
void Now_Playing_Draw(void);
bool Now_Playing_Key(int virtualkey, bool repeat);
