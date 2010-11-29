/*************** <auto-copyright.pl BEGIN do not edit this line> **************
 *
 * VR Juggler is (C) Copyright 1998-2005 by Iowa State University
 *
 * Original Authors:
 *   Allen Bierbaum, Christopher Just,
 *   Patrick Hartling, Kevin Meinert,
 *   Carolina Cruz-Neira, Albert Baker
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * -----------------------------------------------------------------
 * File:          app.cpp,v
 * Date modified: 2005/07/02 14:01:49
 * Version:       1.6.2.1
 * -----------------------------------------------------------------
 *
 *************** <auto-copyright.pl END do not edit this line> ***************/

#include <vrj/Kernel/Kernel.h>
#include <MultiLoadApp.h>

int main(int argc, char* argv[])
{
    vrj::Kernel* kernel      = vrj::Kernel::instance();
    MultiLoadApp*   application = new MultiLoadApp(kernel);
    
    application->processArguments(argc, argv);
    
    kernel->start();
    kernel->setApplication(application);
    kernel->waitForKernelStop();
    
    delete application;
    
    return 0;
}
