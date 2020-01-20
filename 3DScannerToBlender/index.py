import bpy
import builtins as __builtin__
from bpy import context
import serial

FLATBED_DIM = {'x':20, 'y': 30, 'z' : 2}

def console_print(*args, **kwargs):
    for a in context.screen.areas:
        if a.type == 'CONSOLE':
            c = {}
            c['area'] = a
            c['space_data'] = a.spaces.active
            c['region'] = a.regions[-1]
            c['window'] = context.window
            c['screen'] = context.screen
            s = " ".join([str(arg) for arg in args])
            for line in s.split("\n"):
                bpy.ops.console.scrollback_append(c, text=line)

def print(*args, **kwargs):
    """Console print() function."""

    console_print(*args, **kwargs) # to py consoles
    __builtin__.print(*args, **kwargs) # to system console
    
    
    

bl_info = {
    "name": "Run 3D Scanner",
    "author": "Audittxl (Asim Poptani)",
    "version": (1, 0),
    "category": "3D Scanner"}


def init() -> list:
#    Remove everything from set
    bpy.ops.object.select_all(action='SELECT')
    bpy.ops.object.delete(use_global=False, confirm=False)
#    Gnereate probe
    bpy.ops.mesh.primitive_cylinder_add()
    probe=bpy.context.active_object
    probe.location.z+=10
    probe.name="Probe"
#   Generate flatbed
    bpy.ops.mesh.primitive_grid_add(size=1, enter_editmode=False, location=(0, 0, 0))
    bpy.context.object.location[0] = FLATBED_DIM['x']/2
    bpy.context.object.location[1] = FLATBED_DIM['y']/2
    bpy.context.object.location[2] = 0
    bpy.context.object.scale[0] = FLATBED_DIM['x']
    bpy.context.object.scale[1] = FLATBED_DIM['y']
    bpy.ops.object.editmode_toggle()
    bpy.ops.mesh.extrude_region_move(MESH_OT_extrude_region={"use_normal_flip":False, "mirror":False}, TRANSFORM_OT_translate={"value":(0, 0,FLATBED_DIM['z']), "orient_type":'NORMAL', "orient_matrix":((0.204538, -0.978859, 0), (0.978859, 0.204538, -0), (0, 0, 1)), "orient_matrix_type":'NORMAL', "constraint_axis":(False, False, True), "mirror":False, "use_proportional_edit":False, "proportional_edit_falloff":'SMOOTH', "proportional_size":1, "use_proportional_connected":False, "use_proportional_projected":False, "snap":False, "snap_target":'CLOSEST', "snap_point":(0, 0, 0), "snap_align":False, "snap_normal":(0, 0, 0), "gpencil_strokes":False, "cursor_transform":False, "texture_space":False, "remove_on_cancel":False, "release_confirm":False, "use_accurate":False})
    bpy.ops.object.editmode_toggle()
    flatbed=bpy.context.active_object
    flatbed.name="Flatbed"
    return [probe,flatbed]


#    TODO : Establish contact with probe
def contactProbe():
    ser = serial.Serial('/dev/ttyUSB0')
    


def main():
    init()
main()