#version 450

//----------------------------------------------------------------------------
// Input Variables
// ----------------------------------------------------------------------------
// There are no custom input variables (except the in-build ones).

// ----------------------------------------------------------------------------
// Output Variables
// ----------------------------------------------------------------------------

// The final output color.
layout(location = 0) out vec4 final_color;

// ----------------------------------------------------------------------------
// Main Method
// ----------------------------------------------------------------------------
void main()
{
    final_color = vec4(1.0, 1.0, 1.0, 1.0);
}
