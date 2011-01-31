#!BPY

# ---------------------------------------------------------------------------- #

"""
Name: 'Playground Mesh (.pme)...'
Blender: 248
Group: 'Export'
Tooltip: 'Export a Playground PME file'
"""

# ---------------------------------------------------------------------------- #

__author__ = ("Mike Kasprzak")
__url__ = ["Sykhronics Entertainment, http://www.sykhronics.com",
"Mike's Blog, http://www.toonormal.com"]
__version__ = "0.1 (2009-05-22)"

# ---------------------------------------------------------------------------- #

__bpydoc__ = """\
This script exports PME files, usable in games developed by/with Sykhronics Entertainment.

Usage:

Run this script from "File->Export" menu.
"""

# ---------------------------------------------------------------------------- #

import Blender
from Blender import sys as bsys
from Blender import Mathutils
from Blender import Lamp
from Blender import Camera
from Blender import Window
import math
import os

# Utility Library, soon to become standardized (BPy is new API) #
import BPyMesh

# ---------------------------------------------------------------------------- #
# Global Vars #
SCN = []		# Current Scene #
EXPORT_DIR = ''	# Export Directory #
# ---------------------------------------------------------------------------- #

# ---------------------------------------------------------------------------- #
def relpath( origin, dest ):
	return origin
# ---------------------------------------------------------------------------- #


# ---------------------------------------------------------------------------- #
def count_verts( mesh ):
	verts = 0
	for face in mesh.faces:
		verts += len(face.verts)
	
	return verts
# ---------------------------------------------------------------------------- #
def count_faces( mesh ):
	faces = 0
	for face in mesh.faces:
		faces += len(face.verts)-2
	
	return faces
# ---------------------------------------------------------------------------- #
def count_materialfaces( mesh, material ):
	faces = 0
	for face in mesh.faces:
		if face.mat == material:
			faces += len(face.verts)-2
	
	return faces
# ---------------------------------------------------------------------------- #
def write_mesh( FP, mesh, obj ):
	FP.write( 'Mesh \"%s\"\n' % obj.getName() )
	FP.write( '	Materials %i\n' % len(mesh.materials) )
	
	for idx in range(len(mesh.materials)):
		material = mesh.materials[idx]
		FP.write( '		Material %i \"%s\"\n' % (idx,material.getName()) )
		for mytex in material.getTextures():
			if mytex:
				if mytex.tex.getType() == 'Image':
					FP.write( '			Image \"%s\"\n' % relpath(mytex.tex.getImage().getFilename(), EXPORT_DIR) )
				else:
					FP.write( '			// Empty Material //\n' )
				
	FP.write( '	Vertices %i\n' % count_verts( mesh ) )
	for face in mesh.faces:
		for idx in range(len(face.verts)):
			v = face.verts[idx]
			
			FP.write( '		Vertex' )
			FP.write( 'Norm' )
			if mesh.faceUV:
				FP.write( 'UV' )
			if mesh.vertexColors:
				FP.write( 'Color' )
			
			FP.write( ' %.6f %.6f %.6f' % tuple(v.co) )
			if face.smooth:
				FP.write( '  %.6f %.6f %.6f' % tuple(v.no) )
			else:
				FP.write( '  %.6f %.6f %.6f' % tuple(face.no) )
			if mesh.faceUV:
				FP.write( '  %.6f %.6f' % tuple(face.uv[idx]) )
			if mesh.vertexColors:
				FP.write( '  %i %i %i %i' % (face.col[idx].r, face.col[idx].a, face.col[idx].b, face.col[idx].a) )
			FP.write( '\n' )

	FP.write( '	Faces %i\n' % count_faces( mesh ) )
	for idx in range(len(mesh.materials)):
		material = mesh.materials[idx]
		FP.write( '		FaceGroup %i\n' % count_materialfaces( mesh, idx ) )
		FP.write( '		UseMaterial %i\n' % idx )
		vert = 0
		for face in mesh.faces:
			if face.mat == idx:
				if len(face.verts) == 3:
					FP.write( '			Face %i %i %i\n' % (vert+0,vert+1,vert+2) )
				elif len(face.verts) == 4:
					FP.write( '			Face %i %i %i\n' % (vert+0,vert+1,vert+2) )
					FP.write( '			Face %i %i %i\n' % (vert+2,vert+3,vert+0) )
				
			vert += len(face.verts)
# ---------------------------------------------------------------------------- #
def write_properties( FP, prop ):
	if prop:
		FP.write( '	Properties\n' )
		for myprop in prop:
			FP.write( '		Property \"%s\" %s ' % (myprop.getName(),myprop.getType()) )
			if myprop.getType() == 'BOOL':
				FP.write( '%s' % myprop.getData() )
			elif myprop.getType() == 'STRING':
				FP.write( '\"%s\"' % myprop.getData() )
			elif myprop.getType() == 'INT':
				FP.write( '%i' % myprop.getData() )
			elif myprop.getType() == 'FLOAT':
				FP.write( '%f' % myprop.getData() )
			elif myprop.getType() == 'TIME':
				FP.write( '%s' % myprop.getData() )
			FP.write( '\n' )
# ---------------------------------------------------------------------------- #

# ---------------------------------------------------------------------------- #
def write_pme(filename):
	global EXPORT_DIR
	
	# Note the start time of this operation, so we can log how long this took #
	StartTime = bsys.time()
	
	# Append ".pme" in case it's missing it #
	if not filename.lower().endswith('.pme'):
		filename += '.pme'

	# 
	export_dir = bsys.dirname(filename)
	if export_dir != EXPORT_DIR:
		EXPORT_DIR = export_dir

	# If I'm in Edit Mode, Change out of it #	
	in_editmode = Window.EditMode()
	if in_editmode:
		Window.EditMode(0)

	# Get the current scene #	
	SCN = Blender.Scene.GetCurrent()
	
	# Open the File #
	file = open( filename, 'wb' )
	
	# Export Data #
	for obj in SCN.objects:
		#print 'Obj %s' % ( obj.getType() )	
		if 'Mesh' == obj.type:
			# getMeshFromObject( Object, Parent, Apply Modifiers, VGroup?, Scene ) #
			mesh = BPyMesh.getMeshFromObject(obj, None, True, False, SCN)
			mesh.transform(obj.matrixWorld)
			write_mesh( file, mesh, obj )
			write_properties( file, obj.getAllProperties() )
			file.write( '\n' )
	
	file.close()
				
#	if not mesh:
#		Blender.Draw.PupMenu('Error%t|Could not get mesh data from active object')
#		return
	
	# If we were in edit mode, restore it #
	if in_editmode:
		Window.EditMode(1)
	
	# Completed - Log the time it took #
	EndTime = bsys.time()
	message = 'Successfully exported "%s" in %.4f seconds' % ( bsys.basename(filename), EndTime-StartTime)
	print message


def main():
	if os.getenv( 'BLENDER_TARGET' ):
		write_pme( os.getenv( 'BLENDER_TARGET' ) )
	else:
		fname = bsys.makename(ext=".pme")
		if EXPORT_DIR <> '':
			fname = bsys.join( EXPORT_DIR, bsys.basename(fname) )
	
		Blender.Window.FileSelector( write_pme, 'PME Export', fname )


if __name__=='__main__':
	main()

