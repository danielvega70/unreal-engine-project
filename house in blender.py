import bpy

# Clear the default scene
bpy.ops.object.select_all(action='SELECT')
bpy.ops.object.delete(use_global=False)

# Create a cube for the main structure of the house
bpy.ops.mesh.primitive_cube_add(size=3)

# Scale the cube to make it the appropriate size for the house
bpy.ops.transform.resize(value=(3, 4, 2))

# Create a pitched roof for the house
bpy.ops.mesh.primitive_plane_add(size=3)
bpy.ops.transform.rotate(value=1.5708, orient_axis='X')

# Move the roof into place on top of the house
bpy.ops.transform.translate(value=(0, 0, 2))

# Create a door for the house
bpy.ops.mesh.primitive_cube_add(size=1)
bpy.ops.transform.resize(value=(1, 2, 0.1))
bpy.ops.transform.translate(value=(0, -1, -1.5))

# Create a window for the house
bpy.ops.mesh.primitive_cube_add(size=1)
bpy.ops.transform.resize(value=(1, 1, 0.1))
bpy.ops.transform.translate(value=(0, 1, -1.5))

# Create materials for the house
house_material = bpy.data.materials.new(name="House Material")
house_material.diffuse_color = (1, 1, 1)
roof_material = bpy.data.materials.new(name="Roof Material")
roof_material.diffuse_color = (0.5, 0.5, 0.5)
door_material = bpy.data.materials.new(name="Door Material")
door_material.diffuse_color = (0.8, 0.4, 0.2)
window_material = bpy.data.materials.new(name="Window Material")
window_material.diffuse_color = (0.7, 0.7, 1)

# Apply the materials to the house, roof, door, and window
house_object = bpy.data.objects["Cube"]
house_object.data.materials.append(house_material)
roof_object = bpy.data.objects["Plane"]
roof_object.data.materials.append(roof_material)
door_object = bpy.data.objects["Cube.001"]
door_object.data.materials.append(door_material)
window_object = bpy.data.objects["Cube.002"]
window_object.data.materials.append(window_material)

# Add lights to the scene
bpy.ops.object.light_add(type='SUN', location=(0, 0, 5))
bpy.ops.object.light_add(type='POINT', location=(0, 0, 2))

# Set the camera position and orientation
camera_location = (0, -8, 4)
camera_rotation = (1.0472, 0, 0.7854)
bpy.context.scene.camera.location = camera_location
bpy.context.scene.camera.rotation_euler = camera_rotation

# Render the scene to an image file
bpy.ops.render.render()
bpy.data.images['Render Result'].save_render(filepath='house.png')
