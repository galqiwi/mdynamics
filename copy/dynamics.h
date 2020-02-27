#pragma once

#include "headers.h"
#include "vector3D.h"

void fix_interaction_coords_link(double& x, double& bounce) {
	if (x > bounce / 2.)
		x = -bounce + x;
	if (x < -bounce / 2.)
		x = bounce + x;
}

void fix_interaction_coords_v_link(Vector3D& x, double& bounce) {
	fix_interaction_coords_link(x.x, bounce);
	fix_interaction_coords_link(x.y, bounce);
	fix_interaction_coords_link(x.z, bounce);
}

Vector3D fix_interaction_coords_v(Vector3D x, double& bounce) {
	fix_interaction_coords_v_link(x, bounce);
	return x;
}

void fix_position_coords_link(double& x, double& bounce) {
	if (x < 0)
		x += bounce;
	if (x >= bounce)
		x -= bounce;
}

void fix_position_coords_v_link(Vector3D& x, double& bounce) {
	fix_position_coords_link(x.x, bounce);
	fix_position_coords_link(x.y, bounce);
	fix_position_coords_link(x.z, bounce);
}

double simple_potential(Vector3D x) {
	double xsq = (x * x);
	double t = (xsq * xsq * xsq);
	return 4 * (1 - t) / (t * t);
}

Vector3D simple_force(Vector3D& x) {
	double xsq = (x * x);
	double t = (xsq * xsq * xsq);
	return (24 * (t - 2) / (t * t * xsq)) * x;
}

double potential(Vector3D x, double& bounce) {
	fix_interaction_coords_v_link(x, bounce);
	return simple_potential(x);
}

Vector3D force(Vector3D x, double& bounce) {
	fix_interaction_coords_v_link(x, bounce);
	return simple_force(x);
}

void thread_full_penergy(int N, Vector3D* particles, double* penergy, double bounce, int thread_id, int NTHREADS) {
	(*penergy) = 0;
	for (int i = thread_id; i < N; i += NTHREADS) {
		for (int k = i + 1; k < N; k++) {
			(*penergy) += potential(particles[i] - particles[k], bounce);
		}
	}
}

double full_penergy(Vector3D* particles, int N, double bounce, thread* threads, int NTHREADS) {
	double* penergy_buffer = new double[NTHREADS];
	for (int i = 0; i < NTHREADS; i++) {
		threads[i] = thread(thread_full_penergy, N, particles, penergy_buffer + i, bounce, i, NTHREADS);
	}
	for (int i = 0; i < NTHREADS; i++) {
		threads[i].join();
	}
	double final_energy = 0;
	for (int i = 0; i < NTHREADS; i++) {
		final_energy += penergy_buffer[i];
	}
	delete penergy_buffer;
	return final_energy;
}

double full_kenergy(Vector3D* particles_v, int N, double bounce) {
	double final_energy = 0;
	for (int i = 0; i < N; i++) {
		final_energy += abs2(particles_v[i]) / 2;
	}
	return final_energy;
}

void print_xyz(ofstream& fout, Vector3D* particles, int N) {
	fout << N << "\n\n";
	for (int i = 0; i < N; i++)
		fout << "X " << particles[i] << "\n";
}

void thread_forces_init(int N, Vector3D* particles_old, Vector3D* forces, double bounce, int thread_id, int NTHREADS) {
	for (int i = thread_id; i < N; i += NTHREADS) {
		for (int k = 0; k < N; k++) {
			if (k == i)
				continue;
			Vector3D force_ = force(particles_old[i] - particles_old[k], bounce);
			forces[i] -= force_;
		}
	}
}

void process_stupid(int N, int NTHREADS, double dt, double bounce, thread* threads,
	Vector3D* particles    , Vector3D* particles_v    , Vector3D* forces    ,
	Vector3D* particles_old, Vector3D* particles_v_old, Vector3D* forces_old) {

	for (int i = 0; i < N; i++) {
		particles[i] = particles_old[i] + particles_v_old[i] * dt + forces_old[i] * (dt * dt / 2);
		fix_position_coords_v_link(particles[i], bounce);
	}

	for (int i = 0; i < N; i++)
		forces[i] = Vector3D(0, 0, 0);

	for (int i = 0; i < NTHREADS; i++) {
		threads[i] = thread(thread_forces_init, N, particles, forces, bounce, i, NTHREADS);
	}
	for (int i = 0; i < NTHREADS; i++) {
		threads[i].join();
	}
	for(int i = 0; i < N; i++) {
		particles_v[i] = particles_v_old[i] + (forces_old[i] + forces[i]) * (dt / 2);
	}
}