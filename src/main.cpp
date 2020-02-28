#include "headers.h"
#include "vector3D.h"
#include "dynamics.h"

void midprocessing(int N, int Nx, Vector3D* particles, Vector3D* particles_v, thread* threads, int NTHREADS, double bounce, double cell_size, int frame/*, long double& sum_energy, long double& sum_energy2, int nframes_start_dispersion*/) {
	long double full_energy = full_penergy(particles, N, bounce, threads, NTHREADS) + full_kenergy(particles_v, N, bounce);
	static long double init_full_energy = full_energy;

	double r2 = 0;

	for (int i = 0; i < N; i++) {
		int tmp = i;
		int x = tmp % Nx;
		tmp /= Nx;
		int y = tmp % Nx;
		tmp /= Nx;
		int z = tmp;
		r2 += abs2(particles[i] - Vector3D(x + .5, y + .5, z + .5) * cell_size);
	}

	r2 /= N;
	
	r2 *= r2;
	cout << frame << "\t" << (full_energy - init_full_energy) / init_full_energy << "\t" << r2 << endl;
	/*
	if (frame >= nframes_start_dispersion) {
		sum_energy += full_energy;
		sum_energy2 += full_energy * full_energy;
	}
	*/
}

void postprocessing(int N, int Nx, Vector3D* particles, Vector3D* particles_v, double bounce) {
	/*
	for (int i = 0; i < N; i++)
		cerr << particles_v[i] << endl;
	*/
}

int main(int argc, char* argv[]) {
	srand (time(NULL));
	
	int Nx = 10;
	int nFrames = 500;
	int nframes_start_dispersion = 250;
	int N = Nx * Nx * Nx;
	double dt = 0.0005;
	int UPF = 10;
	int NTHREADS = 16;
	double cell_size = pow(2, 1/6.);
	double bounce = cell_size * Nx;

	//cin >> UPF;

	Vector3D* particles = new Vector3D[N];
	Vector3D* particles_v = new Vector3D[N];
	Vector3D* particles_old = new Vector3D[N];
	Vector3D* particles_v_old = new Vector3D[N];
	Vector3D* forces = new Vector3D[N];
	Vector3D* forces_old = new Vector3D[N];
	thread* threads = new thread[NTHREADS];
	
	for (int i = 0; i < N; i++) {
		int tmp = i;
		int x = tmp % Nx;
		tmp /= Nx;
		int y = tmp % Nx;
		tmp /= Nx;
		int z = tmp;
		particles[i] = Vector3D(x + .5, y + .5, z + .5) * cell_size;
		particles_v[i] = 100 * (v_rand() - Vector3D(.5, .5, .5));
		forces[i] = Vector3D(0, 0, 0);
	}

	ofstream fout = ofstream("data/data.xyz");

	//long double sum_energy = 0, sum_energy2 = 0;

	for (int frame = 0; frame < nFrames; frame++) {
		print_xyz(fout, particles, N);
		
		midprocessing(N, Nx, particles, particles_v, threads, NTHREADS, bounce, cell_size, frame/*, sum_energy, sum_energy2, nframes_start_dispersion*/);

		for (int i = 0; i < UPF; i++) {
			swap(particles, particles_old);
			swap(particles_v, particles_v_old);
			swap(forces, forces_old);
			process_stupid(N, NTHREADS, dt / UPF, bounce, threads, particles, particles_v, forces, particles_old, particles_v_old, forces_old);
		}
	}

	/*
	sum_energy /= (nFrames - nframes_start_dispersion);
	sum_energy2 /= (nFrames - nframes_start_dispersion);
	long double dispersion = sum_energy2 - sum_energy * sum_energy;
	cerr << UPF << " " << dispersion << " " << sum_energy << endl;
	*/
	//postprocessing(N, Nx, particles, particles_v, bounce);
}



/*
	struct timespec begint, endt;
	clock_gettime(CLOCK_MONOTONIC, &begint);
	
	double full_energy = 0;//full_penergy(particles, N, bounce, threads, NTHREADS) + full_kenergy(particles_v, N, bounce);
	
	clock_gettime(CLOCK_MONOTONIC, &endt);

	static double init_full_energy = full_energy;
	cout << frame << "\t" << (full_energy - init_full_energy) / init_full_energy << "\t" << endt.tv_nsec - begint.tv_nsec << "\t" << endt.tv_sec - begint.tv_sec << endl;
*/